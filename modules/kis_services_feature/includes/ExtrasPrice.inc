<?php

/**
 * Class ExtrasPrice
 */
class ExtrasPrice extends Price {

  private $code;
  private $mandatory;

  /**
   * Service constructor.
   */
  public function __construct($code, $destination_price, $destination_currency, $local_price, $local_currency, $mandatory = FALSE) {
    parent::__construct($destination_price, $destination_currency, $local_price, $local_currency);

    $this->setCode($code);
    $this->setMandatory($mandatory);
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
   * @return mixed
   */
  public function getMandatory()
  {
    return $this->mandatory;
  }

  /**
   * @param mixed $mandatory
   */
  public function setMandatory($mandatory)
  {
    $this->mandatory = $mandatory;
  }


}
