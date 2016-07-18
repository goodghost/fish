<?php

/**
 * Class AccommodationPricingServiceClient
 */
class ExtrasPricingServiceClient extends ServiceClient {
  /**
   * Service constructor. In PricingServiceClient $cache_ttl is optional.
   *
   * @param $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint, $cache_ttl = 0, $access_key = NULL, $access_token = NULL) {
    parent::__construct($endpoint, $cache_ttl, $access_key, $access_token);
  }

  /**
   * Returns prices for extras in given city.
   * Returned prices can be further filtered by providing course, duration and start date requested.
   *
   * @param $city
   * @param $culture_code
   * @param $currency_code
   * @param DateTime $start_date
   * @param $duration
   * @param null $accommodation_code
   * @return mixed|null
   */
  public function getPrices($city, $culture_code, $currency_code, DateTime $start_date, $duration, $accommodation_code = NULL) {
    $path = implode("/", array($city));

    // Build parameters array
    $parameters = array(
      "localCurrencyCode" => $currency_code,
      "localCultureCode" => self::sanitizeCultureCode($culture_code),
      "courseStartDate" => $start_date->format("Y-m-d"),
      "courseDuration" => $duration,
    );

    if ($accommodation_code) {
      $parameters['accommodationCode'] = $accommodation_code;
    }

    // Try calling a service, please.
    try {
      if ($data = $this->get($path, $parameters, variable_get('kis_services_extras_pricing_service_cache', 3600))) {
        return $data;
      }

    } catch (HttpClientException $e) {
      watchdog('kis_pricing_plan', $e->getMessage(), array(), WATCHDOG_ERROR);
    }
  }


  /**
   * Post process returned prices. This method wraps
   *
   * @param $data
   * @return mixed
   */
  protected function postProcess($data) {
    $price_objects = array();
    foreach($data as $price) {
      $price_objects[$price['productCode']] = new ExtrasPrice($price['productCode'], $price['destinationPrice'], $price['destinationCurrency'], $price['localPrice'],  $price['localCurrency'], $price['mandatory']);
    }

    return $price_objects;
  }
}
