<?php

/**
 * @file
 * The API and related functions for executing and managing payments.
 */

/**
 * Base class with common functionality.
 */
class PaymentCommon {
  function __construct(array $properties = array()) {
    foreach ($properties as $property => $value) {
      $this->$property = $value;
    }
  }
}

/**
 * A single payment. Contains all payment-specific data.
 *
 * @see PaymentMethod
 * @see PaymentMethodController
 */
class Payment extends PaymentCommon {

  /**
   * The payment amount.
   *
   * The number of decimals depends on the ISO 4217 currency used.
   *
   * @var float
   */
  public $amount = 0;

  /**
   * The name of a function to call when the payment has been completed. It
   * receives two arguments:
   * - $payment Payment
   *   The Payment object.
   * - $redirect boolean
   *   Whether the user was redirected offsite during payment execution.
   * The callback does not need to return anything and is free to redirect the
   * user or display something.
   * Use $caller_data to pass on arbitrary data to the finish callback.
   *
   * @var string
   */
  public $finish_callback = '';

  /**
   * The Unix datetime the payment was created.
   *
   * @var integer
   */
  public $created = 0;

  /**
   * The ISO 4217 currency code of the amount.
   *
   * @var string
   */
  public $currency_code = 'XXX';

  /**
   * The payment description.
   *
   * @var string
   */
  public $description = '';

  /**
   * The Unix datetime the payment expires.
   *
   * @var integer
   */
  public $expired = 0;

  /**
   * Information about this payment that is specific to the 'context' that
   * created it, such as the webshop.
   *
   * @var array
   */
  public $caller_data = array();

  /**
   * The payment method used for this payment.
   *
   * @var PaymentMethod
   */
  public $method = NULL;

  /**
   * Information about this payment that is specific to its payment method.
   *
   * @var array
   */
  public $method_data = array();

  /**
   * The internal ID of this payment.
   *
   * @var integer
   */
  public $pid = 0;

  /**
   * The status log. Contains PaymentStatusItem objects ordered by datetime.
   *
   * @see Payment::setStatus()
   *
   * @var array
   */
  protected $statuses = array();

  /**
   * The UID of the user this payment belongs to.
   *
   * @var integer
   */
  public $uid = 0;

  /**
   * The Unix datetime the payment was last updated.
   *
   * @var integer
   */
  public $updated = 0;

  /**
   * Constructor.
   *
   * @param $properties array
   *   An associative array. Keys are property names and values are property
   *   values.
   *
   * @return NULL
   */
  function __construct(array $properties = array()) {
    global $user;

    parent::__construct($properties);

    if (!$this->uid) {
      $this->uid = $user->uid;
    }
    if (!$this->created) {
      $this->created = time();
    }
    if (!$this->statuses) {
      // We purposefully avoid Payment::setStatus(), because this is the
      // payment's first status.
      $this->statuses[] = new PaymentStatusItem(PAYMENT_STATUS_NEW);
    }
  }

  /**
   * Execute the actual payment.
   *
   * @return NULL
   */
  function execute() {
    // Preprocess the payment.
    module_invoke_all('payment_pre_execute', $this);
    if (module_exists('rules')) {
      rules_invoke_event('payment_pre_execute', $this);
    }
    // Execute the payment.
    if ($this->method && $this->method->controller->validate($this)) {
      $this->setStatus(new PaymentStatusItem(PAYMENT_STATUS_PENDING));
      $this->method->controller->execute($this);
    }
    else {
      $this->setStatus(new PaymentStatusItem(PAYMENT_STATUS_FAILED));
    }
    // This is only called if the payment execution didn't redirect the user
    // offsite. Otherwise it's the payment method return page's responsibility.
    $this->finish(FALSE);
  }

  /**
   * Finish the payment after its execution.
   *
   * @return NULL
   */
  function finish() {
    entity_save('payment', $this);
    call_user_func($this->finish_callback, $this);
  }

  /**
   * Set the payment status.
   *
   * @param $status_item PaymentStatusItem
   *
   * @return NULL
   */
  function setStatus(PaymentStatusItem $status_item) {
    // A fail-safe to ensure hook implementations are only called if the status
    // has really changed.
    if ($this->getStatus()->code == $status_item->code) {
      return;
    }

    $previous_status_item = $this->getStatus();
    $status_item->pid = $this->pid;
    $this->statuses[] = $status_item;
    foreach (module_implements('payment_status_change') as $module_name) {
      call_user_func($module_name . '_payment_status_change', $this, $previous_status_item);
      // If a hook invocation has added another log item, a new loop with
      // invocations has already been executed and we don't need to continue
      // with this one.
      if ($this->getStatus()->code != $status_item->code) {
        return;
      }
    }
    if (module_exists('rules')) {
      rules_invoke_event('payment_status_change', $this, $previous_status_item);
    }
  }

  /**
   * Set this payment's statuses. hook_payment_status_change() and the
   * corresponding Rules event are NOT fired. This is an internal workaround
   * for PaymentEntityController::attachLoad().
   *
   * @see Payment::setStatus()
   *
   * @param $status_items array
   *
   * @return NULL
   */
  function _setStatuses(array $status_items) {
    if ($status_items) {
      $this->statuses = $status_items;
    }
  }

  /**
   * Get the current payment status.
   *
   * @return PaymentStatusItem
   */
  function getStatus() {
    return end($this->statuses);
  }

  /**
   * Get all this payment's statuses.
   *
   * @var array
   */
  function getStatuses() {
    return $this->statuses;
  }
}

/**
 * Entity API controller for payment entities.
 */
class PaymentEntityController extends EntityAPIController {

  /**
   * Implements EntityAPIController::load().
   */
  function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    foreach ($entities as $payment) {
      // Cast non-string scalars to their original types, because some backends
      // store/return all variables as strings.
      $payment->amount = (float) $payment->amount;
      $payment->created = (int) $payment->created;
      $payment->expired = (int) $payment->expired;
      $payment->pid = (int) $payment->pid;
      $payment->uid = (int) $payment->uid;
      $payment->updated = (int) $payment->updated;
    }

    return $entities;
  }

  /**
   * Implements EntityAPIController::attachLoad().
   */
  function attachLoad(&$queried_entities, $revision_id = FALSE) {
    // Load the payments's payment methods.
    $pmids = array();
    foreach ($queried_entities as $payment) {
      $pmids[] = $payment->pmid;
    }
    $methods = entity_load('payment_method', $pmids);

    // Load the payments's status logs.
    $pids = array_keys($queried_entities);
    $result = db_select('payment_status_item')
      ->fields('payment_status_item')
      ->condition('pid', $pids)
      ->orderBy('created')
      ->execute();
    $status_items = array();
    while ($data = $result->fetchObject()) {
      $status_item = new PaymentStatusItem($data->code, $data->created, $data->pid, $data->psiid);
      $status_items[$status_item->pid][] = $status_item;
    }

    // Add all data to the payments.
    foreach ($queried_entities as $payment) {
      $payment->_setStatuses($status_items[$payment->pid]);
      $payment->method = $methods[$payment->pmid];
      unset($payment->pmid);
    }

    parent::attachLoad($queried_entities, $revision_id);
  }

  /**
   * Implements EntityAPIController::save().
   */
  function save($entity, DatabaseTransaction $transaction = NULL) {
    $payment = $entity;

    // Save the payment.
    $payment->updated = time();
    $payment->pmid = $payment->method->pmid;
    $return = parent::save($payment, $transaction);
    unset($payment->pmid);

    // Save the payment's status items.
    foreach ($payment->getStatuses() as $status_item) {
      // Statuses cannot be edited, so only save the ones without a PSIID set.
      if (!$status_item->psiid) {
        $status_item->pid = $payment->pid;
        drupal_write_record('payment_status_item', $status_item);
      }
    }

    return $return;
  }

  /**
   * Implements EntityAPIController::view().
   */
  function view($entities, $view_mode = 'full', $langcode = NULL, $page = NULL) {
    $build = parent::view($entities, $view_mode, $langcode, $page);
    foreach ($build['payment'] as &$payment_build) {
      $payment = $payment_build['#entity'];

      $status = payment_status_info($payment->getStatus()->code, TRUE);
      $payment_build['status'] = array(
        '#type' => 'item',
        '#title' => t('Status'),
        '#markup' => $status->title,
      );
      $payment_build['amount'] = array(
        '#type' => 'item',
        '#title' => t('Amount'),
        '#markup' => payment_amount_human_readable($payment->amount),
      );
      $payment_build['created'] = array(
        '#type' => 'item',
        '#title' => t('Created'),
        '#markup' => format_date($payment->created),
      );
      $payment_build['updated'] = array(
        '#type' => 'item',
        '#title' => t('Last updated'),
        '#markup' => format_date($payment->updated),
      );
      $rows = array();
      foreach (array_reverse($payment->getStatuses()) as $status_item) {
        $status = payment_status_info($status_item->code);
        $rows[] = array($status->title, format_date($status_item->created));
      }
      $header = array(t('Status'), t('Date'));
      $payment_build['history'] = array(
        '#type' => 'markup',
        '#markup' => theme('table', array(
          'header' => $header,
          'rows' => $rows,
          'caption' => t('Status history'),
        )),
      );
    }

    return $build;
  }
}

/**
 * Payment method configuration.
 *
 * @see Payment
 * @see PaymentMethodController
 */
class PaymentMethod extends PaymentCommon {

  /**
   * The payment method controller this merchant uses.
   *
   * @var PaymentMethodController
   */
  public $controller = NULL;

  /**
   * Information about this payment method that is specific to its controller.
   *
   * @var array
   */
  public $controller_data = array();

  /**
   * The unique internal ID.
   *
   * @var integer
   */
  public $pmid = 0;

  /**
   * The specific human-readable title, e.g. "Paypal WPS".
   *
   * @var string
   */
  public $title_specific = '';

  /**
   * The generic human-readable title, e.g. "Paypal".
   *
   * @var string
   */
  public $title_generic = NULL;
}

/**
 * Entity API controller for payment_method entities.
 */
class PaymentMethodEntityController extends EntityAPIController {

  /**
   * Implements EntityAPIController::load().
   */
  function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    foreach ($entities as $payment) {
      // Cast non-string scalars to their original types, because some backends
      // store/return all variables as strings.
      $payment->pmid = (int) $payment->pmid;
    }

    return $entities;
  }

  /**
   * Implements EntityAPIController::attachLoad().
   */
  function attachLoad(&$queries_entities, $revision_id = FALSE) {
    foreach ($queries_entities as $entity) {
      $entity->controller = payment_method_controller_load($entity->controller_class_name);
      if (!$entity->controller) {
        $entity->controller = payment_method_controller_load('PaymentMethodControllerUnavailable');
      }
      unset($entity->controller_class_name);
    }
    parent::attachLoad($queries_entities, $revision_id);
  }

  /**
   * Implements EntityAPIController::save().
   */
  function save($entity, DatabaseTransaction $transaction = NULL) {
    $entity->controller_class_name = $entity->controller->name;
    $return = parent::save($entity, $transaction);
    unset($entity->controller_class_name);

    return $return;
  }
}

/**
 * A payment method controller, e.g. the logic behind a payment method.
 *
 * @see payment_method_controller_load()
 * @see payment_method_controller_load_multiple()
 *
 * All other payment methods need to extend this class. This is a singleton
 * class. See payment_method_controller_load().
 *
 * @see Payment
 * @see PaymentMethod
 */
class PaymentMethodController {

  /**
   * An array with ISO 4217 currency codes that this controller supports.
   *
   * Leave empty to allow all currencies.
   *
   * @var array
   */
  public $currencies = array();

  /**
   * A human-readable description of this payment method controller.
   *
   * @var string
   */
  public $description = '';

  /**
   * The machine name.
   *
   * This will be set by payment_method_controller_load_multiple() as a
   * shorthand for get_class($payment_method_controller).
   *
   * @see payment_method_controller_load_multiple()
   *
   * @var string
   */
  public $name = '';

  /**
   * The name of the function that returns form elements to configure this
   * payment method for a specific payment. Using #element_validate callbacks,
   * input can be added to the Payment object in $form_state['payment'].
   *
   * @var string
   */
  public $payment_form_elements_callback = '';

  /**
   * The form ID of the payment method settings form.
   *
   * The form's submit callback is expected to add all relevant information to
   * the PaymentMethod object in $form_sate['payment_method], so
   * payment_form_payment_method_submit() can call entity_save() on it.
   *
   * @var string
   */
  public $payment_method_form_id = 'payment_form_payment_method_controller';

  /**
   * The human-readable title.
   *
   * @var array
   */
  public $title = '';

  /**
   * Execute a payment.
   *
   * @param $payment Payment
   *
   * @return boolean
   *   Whether the payment was successfully executed or not.
   */
  function execute(Payment $payment) {}

  /**
   * Validate a payment's data.
   *
   * Because we're dealing with real money, this is a 'last defense' in case
   * payment data is missing or incorrect.
   *
   * @param $payment Payment
   *
   * @return boolean
   *  Whether the payment contains all necessary data for execution.
   */
  function validate(Payment $payment) {
    $valid = TRUE;

    // Confirm the payment amount is higher than 0.
    if ($payment->amount <= 0) {
      $valid = FALSE;
    }

    // Confirm the payment's currency is supported.
    if (!empty($this->currencies) && !in_array($payment->currency_code, $this->currencies)) {
      $valid = FALSE;
    }

    return $valid;
  }
}

/**
 * A payment method controller that essentially disables payment methods.
 *
 * This is a 'placeholder' controller that returns defaults and doesn't really
 * do anything else. It is used when no working controller is available for a
 * payment method, so other modules don't have to check for that.
 */
class PaymentMethodControllerUnavailable extends PaymentMethodController {

  function __construct() {
    $this->title = t('Unavailable');
  }

  /**
   * Implements PaymentMethodController::execute().
   */
  function execute(Payment $payment) {
    $payment->setStatus(new PaymentStatusItem(PAYMENT_STATUS_UNKNOWN));
  }

  /**
   * Implements PaymentMethodController::validate().
   */
  function validate(Payment $payment) {
    return FALSE;
  }
}

/**
 * Form build callback: implements PaymentMethodController payment method form.
 *
 * @return array
 *   A Drupal form.
 */
function payment_form_payment_method_controller(array $form, array &$form_state) {
  return $form;
}

/**
 * A payment status.
 */
class PaymentStatus extends PaymentCommon {

  /**
   * A US English human-readable description.
   *
   * @var string
   */
  public $description = '';

  /**
   * The machine names of this status's parent statuses.
   *
   * @var array
   */
  public $parents = array();

  /**
   * The status code (machine name).
   *
   * @var string
   */
  public $code = '';

  /**
   * A US English human-readable title.
   *
   * @var string
   */
  public $title = '';

  /**
   * Get this payment status's ancestors.
   *
   * @return array
   *   The machine names of this status's ancestors.
   */
  function ancestors() {
    $ancestors = $this->parents;
    foreach ($this->parents as $code) {
      $parent = payment_status_info($code);
      $ancestors += $parent->ancestors();
    }

    return array_unique($ancestors);
  }
}

/**
 * A payment status log item.
 */
class PaymentStatusItem {

  /**
   * The status's machine name.
   *
   * @var string
   */
  public $code = '';

  /**
   * The Unix datetime this status was set.
   *
   * @var integer
   */
  public $created = 0;

  /**
   * The PID of the payment this status item belongs to.
   *
   * @var integer
   */
  public $pid = 0;

  /**
   * The unique internal ID of this payment status item.
   *
   * @var integer
   */
  public $psiid = 0;

  function __construct($code, $created = 0, $pid = 0, $psiid = 0) {
    $this->code = $code;
    $this->created = $created ? $created : time();
    $this->pid = $pid;
    $this->psiid = $psiid;
  }
}