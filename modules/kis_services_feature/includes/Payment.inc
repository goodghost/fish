<?php

/**
 * Class Payment
 */
class Payment {
  public $externalReference;
  public $isDeposit;
  public $transId;
  public $transStatus;
  public $transTime;
  public $authAmount;
  public $authCurrency;
  public $rawAuthMessage;
  public $rawAuthCode;
  public $cardType;
  public $countryMatch;
  public $avs;
  public $threeDSecureAuthentication;
  public $ipAddress;
  public $futurePayId;
  public $futurePayStatusChange;

  public function __construct($order_id, $is_deposit, $transaction_status) {
    $this->setExternalReference($order_id);
    $this->setIsDeposit($is_deposit);
    $this->setTransStatus($transaction_status);
  }
  /**
   * @param mixed $authAmount
   */
  public function setAuthAmount($authAmount)
  {
    $this->authAmount = $authAmount;
  }

  /**
   * @return mixed
   */
  public function getAuthAmount()
  {
    return $this->authAmount;
  }

  /**
   * @param mixed $authCurrency
   */
  public function setAuthCurrency($authCurrency)
  {
    $this->authCurrency = $authCurrency;
  }

  /**
   * @return mixed
   */
  public function getAuthCurrency()
  {
    return $this->authCurrency;
  }

  /**
   * @param mixed $avs
   */
  public function setAvs($avs)
  {
    $this->avs = $avs;
  }

  /**
   * @return mixed
   */
  public function getAvs()
  {
    return $this->avs;
  }

  /**
   * @param mixed $cardType
   */
  public function setCardType($cardType)
  {
    $this->cardType = $cardType;
  }

  /**
   * @return mixed
   */
  public function getCardType()
  {
    return $this->cardType;
  }

  /**
   * @param mixed $countryMatch
   */
  public function setCountryMatch($countryMatch)
  {
    $this->countryMatch = $countryMatch;
  }

  /**
   * @return mixed
   */
  public function getCountryMatch()
  {
    return $this->countryMatch;
  }

  /**
   * @param mixed $futurePayId
   */
  public function setFuturePayId($futurePayId)
  {
    $this->futurePayId = $futurePayId;
  }

  /**
   * @return mixed
   */
  public function getFuturePayId()
  {
    return $this->futurePayId;
  }

  /**
   * @param mixed $futurePayStatusChange
   */
  public function setFuturePayStatusChange($futurePayStatusChange)
  {
    $this->futurePayStatusChange = $futurePayStatusChange;
  }

  /**
   * @return mixed
   */
  public function getFuturePayStatusChange()
  {
    return $this->futurePayStatusChange;
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
   * @param mixed $ipAddress
   */
  public function setIpAddress($ipAddress)
  {
    $this->ipAddress = $ipAddress;
  }

  /**
   * @return mixed
   */
  public function getIpAddress()
  {
    return $this->ipAddress;
  }

  /**
   * @param mixed $isDeposit
   */
  public function setIsDeposit($isDeposit)
  {
    $this->isDeposit = $isDeposit;
  }

  /**
   * @return mixed
   */
  public function getIsDeposit()
  {
    return $this->isDeposit;
  }

  /**
   * @param mixed $rawAuthCode
   */
  public function setRawAuthCode($rawAuthCode)
  {
    $this->rawAuthCode = $rawAuthCode;
  }

  /**
   * @return mixed
   */
  public function getRawAuthCode()
  {
    return $this->rawAuthCode;
  }

  /**
   * @param mixed $rawAuthMessage
   */
  public function setRawAuthMessage($rawAuthMessage)
  {
    $this->rawAuthMessage = $rawAuthMessage;
  }

  /**
   * @return mixed
   */
  public function getRawAuthMessage()
  {
    return $this->rawAuthMessage;
  }

  /**
   * @param mixed $threeDSecureAuthentication
   */
  public function setThreeDSecureAuthentication($threeDSecureAuthentication)
  {
    $this->threeDSecureAuthentication = $threeDSecureAuthentication;
  }

  /**
   * @return mixed
   */
  public function getThreeDSecureAuthentication()
  {
    return $this->threeDSecureAuthentication;
  }

  /**
   * @param mixed $transId
   */
  public function setTransId($transId)
  {
    $this->transId = $transId;
  }

  /**
   * @return mixed
   */
  public function getTransId()
  {
    return $this->transId;
  }

  /**
   * @param mixed $transStatus
   */
  public function setTransStatus($transStatus)
  {
    $this->transStatus = $transStatus;
  }

  /**
   * @return mixed
   */
  public function getTransStatus()
  {
    return $this->transStatus;
  }

  /**
   * @param mixed $transTime
   */
  public function setTransTime($transTime)
  {
    $this->transTime = $transTime;
  }

  /**
   * @return mixed
   */
  public function getTransTime()
  {
    return $this->transTime;
  }
}
