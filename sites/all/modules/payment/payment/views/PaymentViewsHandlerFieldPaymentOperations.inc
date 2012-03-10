<?php

/**
 * Views field handler for a payment's operations links.
 */
class PaymentViewsHandlerFieldPaymentOperations extends views_handler_field {

  /**
   * Implements views_handler_field::render().
   */
  function render($values) {
    $pid = $this->get_value($values);
    $links = menu_contextual_links('payment', 'payment', array($pid));

    return theme('links', array(
      'links' => $links,
      'attributes' => array(
        'class' => array('links', 'inline', 'operations'),
      ),
    ));
  }
}
