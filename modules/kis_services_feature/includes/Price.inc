<?php

/**
 * Class Price
 */
class Price {
  private $destinationPrice;
  private $originalDestinationPrice;
  private $destinationCurrency;
  private $localPrice;
  private $originalLocalPrice;
  private $localCurrency;
  private $promotionCode;
  private $promotion;
  private $cmsDescription;
  private $promotionRuleOperator;
  private $promotionRuleValue;
  private $promotionDuration;
  private $availability;

  /**
   * Service constructor.
   */
  public function __construct($destination_price, $destination_currency, $local_price, $local_currency) {
    $this->setDestinationCurrency($destination_currency);
    $this->setDestinationPrice($destination_price);
    $this->setLocalCurrency($local_currency);
    $this->setLocalPrice($local_price);
  }

  /**
   * @param mixed $originalDestinationPrice
   */
  public function setOriginalDestinationPrice($originalDestinationPrice)
  {
    $this->originalDestinationPrice = $originalDestinationPrice;
  }

  /**
   * @return mixed
   */
  public function getOriginalDestinationPrice()
  {
    return $this->originalDestinationPrice;
  }

  /**
   * @param mixed $originalLocalPrice
   */
  public function setOriginalLocalPrice($originalLocalPrice)
  {
    $this->originalLocalPrice = $originalLocalPrice;
  }

  /**
   * @return mixed
   */
  public function getOriginalLocalPrice()
  {
    return $this->originalLocalPrice;
  }

  /**
   * @param mixed $destinationCurrency
   */
  public function setDestinationCurrency($destinationCurrency)
  {
    $this->destinationCurrency = $destinationCurrency;
  }

  /**
   * @return mixed
   */
  public function getDestinationCurrency()
  {
    return $this->destinationCurrency;
  }

  /**
   * @param mixed $destinationPrice
   */
  public function setDestinationPrice($destinationPrice)
  {
    $this->destinationPrice = $destinationPrice;
  }

  /**
   * @return mixed
   */
  public function getDestinationPrice()
  {
    return $this->destinationPrice;
  }

  /**
   * @param mixed $localCurrency
   */
  public function setLocalCurrency($localCurrency)
  {
    $this->localCurrency = $localCurrency;
  }

  /**
   * @return mixed
   */
  public function getLocalCurrency()
  {
    return $this->localCurrency;
  }

  /**
   * @param mixed $localPrice
   */
  public function setLocalPrice($localPrice)
  {
    $this->localPrice = $localPrice;
  }

  /**
   * @return mixed
   */
  public function getLocalPrice()
  {
    return $this->localPrice;
  }

  /**
   * @param mixed $promotion
   */
  public function setPromotion($promotion)
  {
    $this->promotion = $promotion;
  }

  /**
   * @return mixed
   */
  public function getPromotion()
  {
    return $this->promotion;
  }

  /**
   * @param mixed $description
   */
  public function setCmsDescription($description)
  {
    $this->cmsDescription = $description;
  }

  /**
   * @return mixed
   */
  public function getCmsDescription()
  {
    return $this->cmsDescription;
  }

  /**
   * @param mixed $promotionCode
   */
  public function setPromotionCode($promotionCode)
  {
    $this->promotionCode = $promotionCode;
  }

  /**
   * @return mixed
   */
  public function getPromotionCode()
  {
    return $this->promotionCode;
  }

  /**
   * @param mixed $promotionDuration
   */
  public function setPromotionDuration($promotionDuration)
  {
    $this->promotionDuration = $promotionDuration;
  }

  /**
   * @return mixed
   */
  public function getPromotionDuration()
  {
    return $this->promotionDuration;
  }

  /**
   * @param mixed $promotionRuleOperator
   */
  public function setPromotionRuleOperator($promotionRuleOperator)
  {
    $this->promotionRuleOperator = $promotionRuleOperator;
  }

  /**
   * @return mixed
   */
  public function getPromotionRuleOperator()
  {
    return $this->promotionRuleOperator;
  }

  /**
   * @param mixed $promotionRuleValue
   */
  public function setPromotionRuleValue($promotionRuleValue)
  {
    $this->promotionRuleValue = $promotionRuleValue;
  }

  /**
   * @return mixed
   */
  public function getPromotionRuleValue()
  {
    return $this->promotionRuleValue;
  }

  /**
   * Merge values of two prices.
   *
   * @param Price $price
   *   Price object to merge with.
   */
  public function mergePrices(Price $newPrice) {
    $this->setDestinationPrice($this->getDestinationPrice() + $newPrice->getDestinationPrice());
    $this->setLocalPrice($this->getLocalPrice() + $newPrice->getLocalPrice());
    if ($this->getOriginalDestinationPrice()) {
      $this->setOriginalDestinationPrice($this->getOriginalDestinationPrice() + $newPrice->getDestinationPrice());
      $this->setOriginalLocalPrice($this->getOriginalLocalPrice() + $newPrice->getLocalPrice());
    }
    return $this;
  }

  /**
   * @param mixed $availability
   */
  public function setAvailability($availability)
  {
    $this->availability = $availability;
  }

  /**
   * @return mixed
   */
  public function getAvailability()
  {
    return $this->availability;
  }

  /**
   * Checks if given price offer is available on confirmation
   *
   * @param $threshold
   */
  public function availableOnConfirmation($threshold = 0) {
    return $this->getAvailability() < $threshold;
  }
}
