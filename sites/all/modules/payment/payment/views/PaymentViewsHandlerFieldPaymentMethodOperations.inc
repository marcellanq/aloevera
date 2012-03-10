<?php

/**
 * Views field handler for a payment method's operations links.
 */
class PaymentViewsHandlerFieldPaymentMethodOperations extends views_handler_field {

  /**
   * Implements views_handler_field::render().
   */
  function render($values) {
    $pmid = $this->get_value($values);
    $links = menu_contextual_links('payment', 'admin/config/services/payment/method', array($pmid));

    return theme('links', array(
      'links' => $links,
      'attributes' => array(
        'class' => array('links', 'inline', 'operations'),
      ),
    ));
  }
}
