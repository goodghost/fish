<?php

/**
 * Class Promotion
 */
class Promotion {
  public $code;
  public $description;
  public $duration;
  public $ruleOperator;
  public $ruleValue;
  public $actualLocalPrice;
  public $actualDestinationPrice;

  public $translations;

  /**
   * Class constructor
   *
   * @param $code
   * @param $description
   * @param $rule_operator
   * @param $rule_value
   * @param $actual_local_price
   * @param $actual_destination_price
   * @param $duration
   */
  public function __construct($code, $description, $rule_operator, $rule_value, $actual_local_price, $actual_destination_price, $duration) {
    $this->setCode($code);
    $this->setDescription($description);
    $this->setRuleOperator($rule_operator);
    $this->setRuleValue($rule_value);
    $this->setActualLocalPrice($actual_local_price);
    $this->setActualDestinationPrice($actual_destination_price);
    $this->setDuration($duration);

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
   * @param mixed $description
   */
  public function setDescription($description)
  {
    $this->description = $description;
  }

  /**
   * @return mixed
   */
  public function getDescription()
  {
    return $this->description;
  }

  /**
   * @param mixed $ruleOperator
   */
  public function setRuleOperator($ruleOperator)
  {
    $this->ruleOperator = $ruleOperator;
  }

  /**
   * @return mixed
   */
  public function getRuleOperator()
  {
    return $this->ruleOperator;
  }

  /**
   * @param mixed $actualDestinationPrice
   */
  public function setActualDestinationPrice($actualDestinationPrice)
  {
    $this->actualDestinationPrice = (float) $actualDestinationPrice;
  }

  /**
   * @return mixed
   */
  public function getActualDestinationPrice()
  {
    return $this->actualDestinationPrice;
  }

  /**
   * @param mixed $actualLocalPrice
   */
  public function setActualLocalPrice($actualLocalPrice)
  {
    $this->actualLocalPrice = (float) $actualLocalPrice;
  }

  /**
   * @return mixed
   */
  public function getActualLocalPrice()
  {
    return $this->actualLocalPrice;
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
   * @param mixed $ruleValue
   */
  public function setRuleValue($ruleValue)
  {
    $this->ruleValue = (float) $ruleValue;
  }

  /**
   * @return mixed
   */
  public function getRuleValue()
  {
    return $this->ruleValue;
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
