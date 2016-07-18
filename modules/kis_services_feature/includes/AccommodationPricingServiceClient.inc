<?php

/**
 * Class AccommodationPricingServiceClient
 */
class AccommodationPricingServiceClient extends ServiceClient {
  private $lastCurrencyCode;
  private $lastDuration;
  private $lastCity;
  private $ignorePromotions;

  private $prices = array();

  /**
   * Service constructor. In PricingServiceClient $cache_ttl is optional.
   *
   * @param $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint = NULL, $cache_ttl = 0, $access_key = NULL, $access_token = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('kis_accommodation_pricing_endpoint');
    }

    parent::__construct($endpoint, $cache_ttl, $access_key, $access_token);
  }

  /**
   * Get lowest price from service result.
   *
   * @return AccommodationPrice
   */
  public function getLowestPrice() {
    // Get lowest price.
    foreach ($this->prices as $accommodation_code => $price_object) {
      if (empty($this->lowestPrice)
        || $this->lowestPrice->getDestinationPrice() == 0
        || $price_object->getDestinationPrice() < $this->lowestPrice->getDestinationPrice()) {
        $lowest_price = &$this->prices[$accommodation_code];
      }
    }

    if (!isset($lowest_price)) {
      throw new KisServicesException('Could not fetch price.');
    }

    return $lowest_price;
  }

  /**
   * @param mixed $ignorePromotions
   */
  public function setIgnorePromotions($ignorePromotions)
  {
    $this->ignorePromotions = $ignorePromotions;
  }

  /**
   * @return mixed
   */
  public function getIgnorePromotions()
  {
    return $this->ignorePromotions;
  }

  /**
   * @param mixed $lastCity
   */
  public function setLastCity($lastCity)
  {
    $this->lastCity = $lastCity;
  }

  /**
   * @return mixed
   */
  public function getLastCity()
  {
    return $this->lastCity;
  }

  /**
   * @param mixed $lastCurrencyCode
   */
  public function setLastCurrencyCode($lastCurrencyCode)
  {
    $this->lastCurrencyCode = $lastCurrencyCode;
  }

  /**
   * @return mixed
   */
  public function getLastCurrencyCode()
  {
    return $this->lastCurrencyCode;
  }

  /**
   * @param mixed $lastDuration
   */
  public function setLastDuration($lastDuration)
  {
    $this->lastDuration = $lastDuration;
  }

  /**
   * @return mixed
   */
  public function getLastDuration()
  {
    return $this->lastDuration;
  }

  /**
   * Returns prices for accommodation in given city.
   * Returned prices can be further filtered by providing course, duration and start date requested.
   *
   * @param $city
   * @param $start_date
   * @param $duration
   * @param $currency_code
   * @param $culture_code
   * @param $ignore_promotions
   * @return mixed|null
   */
  public function getPrices($city, DateTime $start_date, $duration, $currency_code, $culture_code, $ignore_promotions = FALSE) {
    $parameters = array(
      'yymm' => $start_date->format('ym'),
      'duration' => $duration,
      'city' => $city,
      'localCurrencyCode' => $currency_code,
      'localCultureCode' => self::sanitizeCultureCode($culture_code),
    );

    $this->setIgnorePromotions($ignore_promotions);
    $this->setLastCity($city);
    $this->setLastCurrencyCode($currency_code);
    $this->setLastDuration($duration);

    // Try calling a service, please.
    try {
      if ($data = $this->get(NULL, $parameters)) {
        return $data;
      }
    }
    catch (HttpClientException $e) {
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
    foreach ($data as $price) {
      $promotion = $price['priceRule'] && !$this->getIgnorePromotions() ? $price['priceRule'] : NULL;
      $this->prices[$price['code']] = new AccommodationPrice($price['code'], $price['duration'], !empty($promotion) ? $promotion['actualDestinationPrice'] : $price['destinationPrice'], $price['destinationCurrency'], !empty($promotion) ? $promotion['actualLocalPrice'] : $price['localPrice'], $price['localCurrency'], $price['spaces']);
      if (!empty($promotion)) {
        $promotion = $price['priceRule'];
        $this->prices[$price['code']]->setOriginalDestinationPrice($price['destinationPrice']);
        $this->prices[$price['code']]->setOriginalLocalPrice($price['localPrice']);
        $this->prices[$price['code']]->setPromotionCode($promotion['code']);
        $this->prices[$price['code']]->setPromotionRuleOperator($promotion['ruleOperator']);
        $this->prices[$price['code']]->setPromotionRuleValue($promotion['ruleValue']);
        $this->prices[$price['code']]->setPromotionDuration($promotion['duration']);
        $this->prices[$price['code']]->setPromotion($promotion['description']);
      }
    }

    return $this->prices;
  }
}
