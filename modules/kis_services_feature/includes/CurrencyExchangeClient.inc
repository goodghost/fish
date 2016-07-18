<?php

/**
 * Class that provides a way to exchange currencies.
 */
class CurrencyExchangeClient extends ServiceClient {
  /**
   * Service constructor. Creates a client with JSON as formatter.
   *
   * @param $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint = NULL, $cache_ttl = NULL, $access_key = NULL, $access_token = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('kis_currency_exchange_endpoint');
    }

    if ($cache_ttl === NULL) {
      $cache_ttl = variable_get('kis_services_currency_exchange_service_cache', 3600);
    }

    parent::__construct($endpoint, $cache_ttl, $access_key, $access_token);
  }

  /**
   * Exchange any amount of money between two currencies.
   *
   * @param string $currency_from
   *   Source currency to change from.
   * @param string $currency_to
   *   Target currency to change to.
   * @param float $amount
   *   Amount of money to exchange.
   *
   * @return int
   *   Amount of money in requested currency.
   */
  public function exchange($currency_from, $currency_to, $amount) {
    try {
      $path = implode('/', func_get_args());

      if ($data = $this->get($path)) {
        return $data;
      }
    }
    catch (HttpClientException $e) {
      watchdog_exception('kis_services', $e);
    }
  }
}
