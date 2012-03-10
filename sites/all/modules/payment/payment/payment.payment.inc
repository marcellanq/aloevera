<?php

/**
 * @file
 * Payment hooks.
 */

/**
 * Implements hook_payment_status_info().
 */
function payment_payment_status_info() {
  return array(
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_MONEY_TRANSFERRED,
      'title' => t('Money has been transferred'),
    )),
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_MONEY_NOT_TRANSFERRED,
      'title' => t('No money has been transferred'),
    )),
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_UNKNOWN,
      'title' => t('Unknown'),
    )),
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_PENDING,
      'title' => t('Pending'),
      'parents' => array(PAYMENT_STATUS_MONEY_NOT_TRANSFERRED),
    )),
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_SUCCESS,
      'title' => t('Completed'),
      'parents' => array(PAYMENT_STATUS_MONEY_TRANSFERRED),
    )),
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_FAILED,
      'title' => t('Failed'),
      'parents' => array(PAYMENT_STATUS_MONEY_NOT_TRANSFERRED),
    )),
    new PaymentStatus(array(
      'code' => PAYMENT_STATUS_NEW,
      'title' => t('Created'),
      'parents' => array(PAYMENT_STATUS_MONEY_NOT_TRANSFERRED),
    )),
  );
}

/**
 * Implements hook_payment_method_controller_info().
 */
function payment_payment_method_controller_info() {
  return array('PaymentMethodControllerUnavailable');
}