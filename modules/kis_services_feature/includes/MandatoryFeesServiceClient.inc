<?php

/**
 * Class MandatoryFeesServiceClient
 */
class MandatoryFeesServiceClient extends ServiceClient {
  /**
   * Service constructor. In MandatoryFeesServiceClient $cache_ttl is optional.
   *
   * @param $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint = NULL, $cache_ttl = 0, $access_key = NULL, $access_token = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('kis_mandatory_fees_pricing_endpoint');
    }

    parent::__construct($endpoint, $cache_ttl, $access_key, $access_token);
  }

  /**
   * Returns prices for given culture code, currency and schools.
   * Returned prices can be further filtered by providing course, duration and start date requested.
   *
   * @param $culture_code
   * @param $currency_code
   * @param $schools
   * @param array $courses
   * @param DateTime $date
   * @param null $duration
   * @return mixed|null
   */
  public function getPrices($culture_code, $currency_code, $countries = array(), DateTime $date = NULL, $duration = NULL, $reset = FALSE) {
    // Build parameters array
    $parameters = array(
      "localCultureCode" => self::sanitizeCultureCode($culture_code),
      "localCurrencyCode" => $currency_code,
    );

    if (!empty($countries)) {
      $parameters['countryCodes'] = implode(",", $countries);
    }

    if ($date) {
      $parameters['courseStartDate'] = $date->format("Y-m-d");
    }

    if ($duration) {
      $parameters['courseDuration'] = $duration;
    }

    // Try calling a service, please.
    try {
      if ($data = $this->get(NULL, $parameters, $this->getCacheTtl(), $reset)) {
        return $data;
      }
    } catch (HttpClientException $e) {
      watchdog('kis_services', $e->getMessage(), array(), WATCHDOG_ERROR);
    }
  }

  /**
   * Post process returned prices and sanitise the output.
   *
   * @param $data
   * @return mixed
   */
  protected function postProcess($data) {
    $mandatory_fees = array();

    if (!empty($data)) {
      // Normalize fees data
      foreach ($data as $fkey => $country) {
        foreach ($country['cities'] as $ckey => $city) {
          foreach ($city['extras'] as $ekey => $extra) {
            if ($extra['mandatory']) {
              $mandatory_fees[$country['regionCode']][$city['name']][$extra['productCode']] = $extra;
            }
          }
        }
      }
    }

    return $mandatory_fees;
  }
}
