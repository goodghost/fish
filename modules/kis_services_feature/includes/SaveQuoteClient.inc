<?php

/**
 * Class SaveQuoteService
 */
class SaveQuoteClient extends ServiceClient {
  /**
   * @param Quote $quote
   * @return mixed|null
   */
  public function saveQuote(Quote $quote) {
    // Build parameters array
    $parameters = array();

    if ($data = $this->post($quote, $parameters)) {
      $response_headers = $this->get_reponse_headers();

      // Poll the returning service for a response.
      if (isset($response_headers['Location'])) {
        $poll_url = $response_headers['Location'];

        $client = new HttpClient(new KisServiceClientAuth(
            variable_get("kis_service_access_key", "access_token"),
            variable_get("kis_service_access_token", "kicbus")),
          new HttpClientJSONFormatter(), FALSE, new HttpClientCurlDelegate());

        // Poll the service for confirmation ID.
        $confirmation_id = NULL;
        // 3 attempts, one second delay before every new one.
        // We don't want the user to wait for too long.
        for ($i = 0; $i <= 3; $i++) {
          sleep(1);
          $confirmation_id = $client->get($poll_url);
          // If available add it to current order and stop polling.
          if (!empty($confirmation_id)) {
            $order_id = $quote->getExternalReference();
            $order = commerce_order_load($order_id);
            $order->field_guid[LANGUAGE_NONE][0]['value'] = $confirmation_id;
            commerce_order_save($order);
            watchdog('kis_services', "Posted saved quote for order @order_id successfully.", array('@order_id' => $order_id), WATCHDOG_INFO);

            break;
          }
        }
        // If we couldn't retrieve confirmation_id, log that event and keep on.
        if (empty($confirmation_id)) {
          watchdog('kis_services', "There was an error retrieving confirmation ID for order @order_id.", array('@order_id' => $order_id), WATCHDOG_WARNING);
        }
      }

      return $data;
    }
  }
}
