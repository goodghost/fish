<?php

class Extra {
  public $code;
  public $localPrice;
  public $destinationPrice;

  public $translations;

  public function __construct($code, $destination_price, $local_price) {
    $this->setCode($code);
    $this->setDestinationPrice($destination_price);
    $this->setLocalPrice($local_price);

    $this->translations = array();
  }

  /**
   * @param mixed $code
   */
  public function setCode($code)
  {
    $this->code = $code;
  }

  /**
   * @return mixed
   */
  public function getCode()
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
}
