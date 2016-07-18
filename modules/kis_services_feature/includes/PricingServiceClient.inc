<?php

/**
 * Class PricingServiceClient
 */
class PricingServiceClient extends ServiceClient {
  /**
   * Service constructor. In PricingServiceClient $cache_ttl is optional.
   *
   * @param $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint = NULL, $cache_ttl = 0, $access_key = NULL, $access_token = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('kis_advanced_search_endpoint');
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
  public function getPrices($culture_code, $currency_code, $schools = array(), $courses = array(), DateTime $date = NULL, $duration = NULL, $lowest_price = FALSE, $reset = FALSE) {
    // Build parameters array
    $parameters = array(
      "localCultureCode" => self::sanitizeCultureCode($culture_code),
      "localCurrencyCode" => $currency_code,
    );

    if ($lowest_price) {
      $parameters['lowestPrice'] = 'true';
    }

    if (!empty($schools)) {
      $parameters['schoolCodes'] = implode(",", $schools);
    }

    if (!empty($courses)) {
      $parameters['courseCodes'] = implode(",", $courses);
    }

    if ($date) {
      $parameters['yymm'] = $date->format("ym");
    }

    if ($duration) {
      $parameters['duration'] = $duration;
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
   * Post process returned prices. This function orders the prices by cheapest.
   *
   * @param $data
   * @return mixed
   */
  protected function postProcess($data) {

    // Sort promotions from cheapest to most expensive
    foreach($data as $skey => $school) {
      foreach($school['courses'] as $ckey => $course) {
        foreach($course['prices'] as $pkey => $price) {
          // Sort
          usort($data[$skey]['courses'][$ckey]['prices'][$pkey]['startDates'], function($a, $b) {
            // Apply promotion first
            $destination_price_a = isset($a['priceRule'])
              ? $a['priceRule']['actualDestinationPrice']
              : PHP_INT_MAX;
            $destination_price_b = isset($b['priceRule'])
              ? $b['priceRule']['actualDestinationPrice']
              : PHP_INT_MAX;

            return $destination_price_a < $destination_price_b ? -1 : 1;
          });
        }
      }
    }

    // Sort price objects from cheapest to most expensive
    foreach($data as $skey => $school) {
      foreach($school['courses'] as $ckey => $course) {
        // Check if we have prices for this course.
        // If not, please remove it from the array as it's
        if (empty($data[$skey]['courses'][$ckey]['prices'])) {
          watchdog('kis_service', 'No prices for course %course at school %school', array('%course' => $ckey, '%school' => $skey), WATCHDOG_WARNING);
          unset($data[$skey]['courses'][$ckey]);

        // Otherwise sort the prices from cheapest to to the most expensive
        } else {
          usort($data[$skey]['courses'][$ckey]['prices'], function ($a, $b) {
            // Apply promotion first
            $destination_price_a = isset($a['startDates'][0]['priceRule'])
              ? $a['startDates'][0]['priceRule']['actualDestinationPrice']
              : $a['destinationPrice'];
            $destination_price_b = isset($b['startDates'][0]['priceRule'])
              ? $b['startDates'][0]['priceRule']['actualDestinationPrice']
              : $b['destinationPrice'];

            return $destination_price_a < $destination_price_b ? -1 : 1;
          });
        }
      }
    }

    // Sort courses from cheapest to the most expensive
    foreach($data as $skey => $school) {
      usort($data[$skey]['courses'], function($a, $b) {
        // Get first price from the list of duration prices.
        // This function assumes prices are already sorted from cheapest to most expensive
        $price_a = current($a['prices']);
        $price_b = current($b['prices']);

        // Apply promotion.
        // This function assumes promotions are already sorted by cheapest
        $destination_price_a = isset($price_a['startDates'][0]['priceRule'])
          ? $price_a['startDates'][0]['priceRule']['actualDestinationPrice']
          : $price_a['destinationPrice'];
        $destination_price_b = isset($price_b['startDates'][0]['priceRule'])
          ? $price_b['startDates'][0]['priceRule']['actualDestinationPrice']
          : $price_b['destinationPrice'];

        return $destination_price_a < $destination_price_b ? -1 : 1;
      });
    }

    return $data;
  }
}
