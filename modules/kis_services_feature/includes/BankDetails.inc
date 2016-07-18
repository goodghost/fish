<?php

/**
 * Class BankDetails
 */
class BankDetails {
  public $bankName;
  public $poBox;
  public $addressLine1;
  public $addressLine2;
  public $city;
  public $postCode;
  public $country;
  public $accountName;
  public $accountNumber;
  public $sortCodeBranchNo;
  public $iban;
  public $swift;

  /**
   * Personal object constructor;
   */
  public function __construct($bank_name) {
    $this->setBankName($bank_name);
  }

  /**
   * @param mixed $accountName
   */
  public function setAccountName($accountName)
  {
    $this->accountName = $accountName;
  }

  /**
   * @return mixed
   */
  public function getAccountName()
  {
    return $this->accountName;
  }

  /**
   * @param mixed $accountNumber
   */
  public function setAccountNumber($accountNumber)
  {
    $this->accountNumber = $accountNumber;
  }

  /**
   * @return mixed
   */
  public function getAccountNumber()
  {
    return $this->accountNumber;
  }

  /**
   * @param mixed $addressLine1
   */
  public function setAddressLine1($addressLine1)
  {
    $this->addressLine1 = $addressLine1;
  }

  /**
   * @return mixed
   */
  public function getAddressLine1()
  {
    return $this->addressLine1;
  }

  /**
   * @param mixed $addressLine2
   */
  public function setAddressLine2($addressLine2)
  {
    $this->addressLine2 = $addressLine2;
  }

  /**
   * @return mixed
   */
  public function getAddressLine2()
  {
    return $this->addressLine2;
  }

  /**
   * @param mixed $bankName
   */
  public function setBankName($bankName)
  {
    $this->bankName = $bankName;
  }

  /**
   * @return mixed
   */
  public function getBankName()
  {
    return $this->bankName;
  }

  /**
   * @param mixed $city
   */
  public function setCity($city)
  {
    $this->city = $city;
  }

  /**
   * @return mixed
   */
  public function getCity()
  {
    return $this->city;
  }

  /**
   * @param mixed $country
   */
  public function setCountry($country)
  {
    $this->country = $country;
  }

  /**
   * @return mixed
   */
  public function getCountry()
  {
    return $this->country;
  }

  /**
   * @param mixed $iban
   */
  public function setIban($iban)
  {
    $this->iban = $iban;
  }

  /**
   * @return mixed
   */
  public function getIban()
  {
    return $this->iban;
  }

  /**
   * @param mixed $poBox
   */
  public function setPoBox($poBox)
  {
    $this->poBox = $poBox;
  }

  /**
   * @return mixed
   */
  public function getPoBox()
  {
    return $this->poBox;
  }

  /**
   * @param mixed $postCode
   */
  public function setPostCode($postCode)
  {
    $this->postCode = $postCode;
  }

  /**
   * @return mixed
   */
  public function getPostCode()
  {
    return $this->postCode;
  }

  /**
   * @param mixed $sortCodeBranchNo
   */
  public function setSortCodeBranchNo($sortCodeBranchNo)
  {
    $this->sortCodeBranchNo = $sortCodeBranchNo;
  }

  /**
   * @return mixed
   */
  public function getSortCodeBranchNo()
  {
    return $this->sortCodeBranchNo;
  }

  /**
   * @param mixed $swift
   */
  public function setSwift($swift)
  {
    $this->swift = $swift;
  }

  /**
   * @return mixed
   */
  public function getSwift()
  {
    return $this->swift;
  }


}
