<?php

/**
 * Class CoursePrice
 */
class CoursePrice extends Price {
  private $start_date;
  private $duration;
  private $school_code;

  /**
   * Service constructor.
   */
  public function __construct($destination_price, $destination_currency, $local_price, $local_currency, DateTime $start_date, $duration) {
    parent::__construct($destination_price, $destination_currency, $local_price, $local_currency);

    $this->setStartDate($start_date);
    $this->setDuration($duration);
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

  /**
   * @param mixed $start_date
   */
  public function setStartDate(DateTime $start_date)
  {
    $this->start_date = $start_date;
  }

  /**
   * @return mixed
   */
  public function getStartDate()
  {
    return $this->start_date;
  }

  /**
   * @param mixed $start_date
   */
  public function setSchoolCode($school_code)
  {
    $this->school_code = $school_code;
  }

  /**
   * @return mixed
   */
  public function getSchoolCode()
  {
    return $this->school_code;
  }
}
