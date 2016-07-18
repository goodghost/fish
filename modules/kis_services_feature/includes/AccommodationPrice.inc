<?php

/**
 * Class AccommodationPrice
 */
class AccommodationPrice extends Price {

  private $code;
  private $duration;

  /**
   * Service constructor.
   */
  public function __construct($code, $duration, $destination_price, $destination_currency, $local_price, $local_currency, $spaces) {
    parent::__construct($destination_price, $destination_currency, $local_price, $local_currency);

    $this->setCode($code);
    $this->setDuration($duration);
    $this->setAvailability($spaces);
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
   * @param mixed $duration
   */
  public function setDuration($duration)
  {
    $this->duration = $duration;
  }

  /**
   * @return mixed
   */
  public function getDuration()
  {
    return $this->duration;
  }

}