<?php

class Course {
  public $code;
  public $duration;
  public $startDate;
  public $localPrice;
  public $destinationPrice;
  public $priceRule;

  public $translations;

  /**
   * Constructor
   *
   * @param $code
   * @param $start_date
   * @param $duration
   * @param $local_price
   * @param $destination_price
   */
  public function __construct($code, $start_date, $duration, $local_price, $destination_price) {
    $this->setCode($code);
    $this->setStartDate($start_date);
    $this->setDuration($duration);
    $this->setLocalPrice($local_price);
    $this->setDestinationPrice($destination_price);

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
   * @param mixed $duration
   */
  public function setDuration($duration)
  {
    $this->duration = (int) $duration;
  }

  /**
   * @return mixed
   */
  public function getDuration()
  {
    return $this->duration;
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
   * @param mixed $startDate
   */
  public function setStartDate(DateTime $startDate)
  {
    // Internally rewrite to this format is required as Mule expects string in specific format.
    // This way also this object will serialise easily.
    
    // We don't care about TIME component here, but to satisfy Mule's validation rules, we have to supply it.
    // The reason we're setting it to 12:00 is to cater for any time transformations downstream that could tip the date over to previous or next day.
    $this->startDate = $startDate->format('Y-m-d\T12:00:00\Z');
  }

  /**
   * @return mixed
   */
  public function getStartDate()
  {
    // When fetching we want to rewrite the string back to DateTime object so PHP can use it easily.
    return  DateTime::createFromFormat('Y-m-d\TH:i:s\Z', $this->startDate);
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
