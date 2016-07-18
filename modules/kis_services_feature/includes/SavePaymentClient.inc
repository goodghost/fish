<?php

/**
 * Class SavePaymentService
 */
class SavePaymentClient extends ServiceClient {
  /**
   * @param Payment $payment
   * @return mixed|null
   */
  public function savePayment(Quote $payment) {
    // Build parameters array
    $parameters = array();

    if ($data = $this->post($payment, $parameters)) {
      return $data;
    }
  }
}
