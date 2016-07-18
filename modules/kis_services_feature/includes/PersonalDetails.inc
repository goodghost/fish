<?php

/**
 * Class Personal
 */
class PersonalDetails {
  public $firstName;
  public $surname;
  public $gender;
  public $dateOfBirth;
  public $nationality;
  public $addressLine1;
  public $addressLine2;
  public $city;
  public $postCode;
  public $county;
  public $country;
  public $phoneNumber;
  public $email;
  public $termsConfirmation;
  public $shareData;

  /**
   * Personal object constructor;
   *
   * @param $first_name
   * @param $surname
   * @param $email
   * @param $phone_number
   * @param $country
   * @param bool $share_data
   * @param bool $confirmation
   */
  public function __construct($first_name = "", $surname = "", $email = "", $phone_number = "", $country = "", $share_data = FALSE, $confirmation = TRUE) {
    $this->setFirstName($first_name);
    $this->setSurname($surname);
    $this->setEmail($email);
    $this->setPhoneNumber($phone_number);
    $this->setCountry($country);
    $this->setShareData($share_data);
    $this->setTermConfirmation($confirmation);
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
   * @param mixed $email
   */
  public function setEmail($email)
  {
    $this->email = $email;
  }

  /**
   * @return mixed
   */
  public function getEmail()
  {
    return $this->email;
  }

  /**
   * @param mixed $firstName
   */
  public function setFirstName($firstName)
  {
    $this->firstName = $firstName;
  }

  /**
   * @return mixed
   */
  public function getFirstName()
  {
    return $this->firstName;
  }


  /**
   * @param mixed $phoneNumber
   */
  public function setPhoneNumber($phoneNumber)
  {
    $this->phoneNumber = $phoneNumber;
  }

  /**
   * @return mixed
   */
  public function getPhoneNumber()
  {
    return $this->phoneNumber;
  }

  /**
   * @param mixed $shareData
   */
  public function setShareData($shareData)
  {
    $this->shareData = (bool) $shareData;
  }

  /**
   * @return mixed
   */
  public function getShareData()
  {
    return $this->shareData;
  }

  /**
   * @param mixed $surname
   */
  public function setSurname($surname)
  {
    $this->surname = $surname;
  }

  /**
   * @return mixed
   */
  public function getSurname()
  {
    return $this->surname;
  }

  /**
   * @param mixed $termsConfirmation
   */
  public function setTermConfirmation($termsConfirmation)
  {
    $this->termsConfirmation = (bool) $termsConfirmation;
  }

  /**
   * @return mixed
   */
  public function getTermConfirmation()
  {
    return $this->termsConfirmation;
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
   * @param mixed $dateOfBirth
   */
  public function setDateOfBirth(DateTime $dateOfBirth)
  {
    // We don't care about TIME component here, but to satisfy Mule's validation rules, we have to supply it.
    // The reason we're setting it to 12:00 is to cater for any time transformations downstream that could tip the date over to previous or next day.
    $this->dateOfBirth = $dateOfBirth->format('Y-m-d\T12:00:00\Z');
  }

  /**
   * @return DateTime
   */
  public function getDateOfBirth()
  {
    return DateTime::createFromFormat('Y-m-d\TH:i:s\Z', $this->dateOfBirth);
  }

  /**
   * @param mixed $gender
   */
  public function setGender($gender)
  {
    $this->gender = $gender;
  }

  /**
   * @return mixed
   */
  public function getGender()
  {
    return $this->gender;
  }

  /**
   * @param mixed $nationality
   */
  public function setNationality($nationality)
  {
    $this->nationality = $nationality;
  }

  /**
   * @return mixed
   */
  public function getNationality()
  {
    return $this->nationality;
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
   * @param mixed $county
   */
  public function setCounty($county)
  {
    $this->county = $county;
  }

  /**
   * @return mixed
   */
  public function getCounty()
  {
    return $this->county;
  }
}
