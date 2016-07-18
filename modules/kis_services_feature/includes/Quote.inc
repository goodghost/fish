<?php

/**
 * Class Quote
 */
class Quote {
  public $bookingType;
  public $schoolId;
  public $localCurrencyCode;
  public $market;
  public $total;
  public $externalReference;

  public $course;
  public $extras;
  public $accommodation;
  public $personalData;
  public $bankTransferData;
  public $paymentResult;

  public $translations;

  public function __construct($type, $order_id, $school_id, $market, $local_currency_code, $total) {
    $this->extras = array();
    $this->setBookingType($type);
    $this->setExternalReference($order_id);
    $this->setSchoolId($school_id);
    $this->setMarket(ServiceClient::sanitizeCultureCode($market));
    $this->setLocalCurrencyCode($local_currency_code);
    $this->setTotal($total);

    $this->translations = array();
  }

  /**
   * @param mixed $accommodation
   */
  public function setAccommodation($accommodation)
  {
    $this->accommodation = $accommodation;
  }

  /**
   * @return mixed
   */
  public function getAccommodation()
  {
    return $this->accommodation;
  }

  /**
   * @param mixed $course
   */
  public function setCourse($course)
  {
    $this->course = $course;
  }

  /**
   * @return mixed
   */
  public function getCourse()
  {
    return $this->course;
  }

  /**
   * @param mixed $extras
   */
  public function addExtras($extras)
  {
    $this->extras[] = $extras;
  }

  /**
   * @return mixed
   */
  public function getExtras()
  {
    return $this->extras;
  }

  /**
   * @param mixed $localCurrencyCode
   */
  public function setLocalCurrencyCode($localCurrencyCode)
  {
    $this->localCurrencyCode = $localCurrencyCode;
  }

  /**
   * @return mixed
   */
  public function getLocalCurrencyCode()
  {
    return $this->localCurrencyCode;
  }

  /**
   * @param mixed $market
   */
  public function setMarket($market)
  {
    $this->market = $market;
  }

  /**
   * @return mixed
   */
  public function getMarket()
  {
    return $this->market;
  }

  /**
   * @param mixed $personalData
   */
  public function setPersonalData($personalData)
  {
    $this->personalData = $personalData;
  }

  /**
   * @return mixed
   */
  public function getPersonalData()
  {
    return $this->personalData;
  }

  /**
   * @param mixed $bankDetails
   */
  public function setBankDetails($bankDetails)
  {
    $this->bankTransferData = $bankDetails;
  }

  /**
   * @return mixed
   */
  public function getBankDetails()
  {
    return $this->bankTransferData;
  }

  /**
   * @param mixed $schoolId
   */
  public function setSchoolId($schoolId)
  {
    $this->schoolId = $schoolId;
  }

  /**
   * @return mixed
   */
  public function getSchoolId()
  {
    return $this->schoolId;
  }

  /**
   * @param mixed $total
   */
  public function setTotal($total)
  {
    $this->total = $total;
  }

  /**
   * @return mixed
   */
  public function getTotal()
  {
    return $this->total;
  }

  /**
   * @param mixed $externalReference
   */
  public function setExternalReference($externalReference)
  {
    $this->externalReference = $externalReference;
  }

  /**
   * @return mixed
   */
  public function getExternalReference()
  {
    return $this->externalReference;
  }

  /**
   * @param mixed $bookingType
   */
  public function setBookingType($bookingType)
  {
    $this->bookingType = $bookingType;
  }

  /**
   * @return mixed
   */
  public function getBookingType()
  {
    return $this->bookingType;
  }

  /**
   * @param mixed $paymentResult
   */
  public function setPaymentResult($paymentResult)
  {
    $this->paymentResult = $paymentResult;
  }

  /**
   * @return mixed
   */
  public function getPaymentResult()
  {
    return $this->paymentResult;
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
