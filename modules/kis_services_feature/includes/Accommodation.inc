<?php

/**
 * Class Accommodation
 */
class Accommodation {
  public $code;
  public $destinationPrice;
  public $localPrice;
  public $accommodationType;
  public $accommodationConfirmed;
  public $priceRule;

  public $translations;

  const RESIDENCE = 1;
  const HOMESTAY = 2;

  /**
   * Constructor for accommodation object.
   *
   * @param $product_id
   * @param $type_id
   * @param $product_code
   * @param $duration
   */
  public function __construct($product_code, $product_type, $destination_price, $local_price, $confirmed) {
    $this->setProductCode($product_code);
    $this->setAccommodationType($product_type);
    $this->setDestinationPrice($destination_price);
    $this->setLocalPrice($local_price);
    $this->setAccommodationConfirmed($confirmed);

    $this->translations = array();
  }

  /**
   * @param mixed $productCode
   */
  public function setProductCode($productCode)
  {
    $this->code = $productCode;
  }

  /**
   * @return mixed
   */
  public function getProductCode()
  {
    return $this->code;
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
    $this->priceRule = $promotion;
  }

  /**
   * @return mixed
   */
  public function getPromotion()
  {
    return $this->priceRule;
  }

  /**
   * @param mixed $accommodationConfirmed
   */
  public function setAccommodationConfirmed($accommodationConfirmed)
  {
    $this->accommodationConfirmed = $accommodationConfirmed;
  }

  /**
   * @return mixed
   */
  public function getAccommodationConfirmed()
  {
    return $this->accommodationConfirmed;
  }

  /**
   * @return array
   */
  public function getTransations() {
    return $this->translations;
  }

  /**
   * @param $key
   * @param $value
   */
  public function addTranslation($key, $value) {
    $this->translations = array(
      'key' => $key,
      'value' => $value,
    );
  }

  /**
   * @return mixed
   */
  public function getAccommodationType()
  {
    return $this->accommodationType;
  }

  /**
   * @param mixed $accommodationType
   */
  public function setAccommodationType($accommodationType)
  {
    $this->accommodationType = $accommodationType;
  }


}
