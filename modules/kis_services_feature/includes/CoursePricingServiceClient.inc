<?php

/**
 * Class CoursePricingServiceClient
 */
class CoursePricingServiceClient extends PricingServiceClient {
  private $prices = array();

  /**
   * Post process returned prices. This method wraps
   *
   * @param $data
   * @return mixed
   */
  protected function postProcess($data) {
    $this->prices = parent::postProcess($data);
    return $this->prices;
  }

  public function getPrices($culture_code, $currency_code, $schools = array(), $courses = array(), DateTime $date = NULL, $duration = NULL, $start_date_key = NULL, $lowest_price = FALSE) {
    $result = parent::getPrices($culture_code, $currency_code, $schools, $courses, $date, $duration, $lowest_price);
    return $result;
  }

  /**
   * Get lowest price from service call result.
   *
   * @return array
   */
  public function getLowestPrice($start_date_key = 0) {
    $lowest_price = NULL;
    foreach ($this->prices as $course_price) {
      $price = $course_price['courses'][0]['prices'][0];

      if (empty($lowest_price) || $price['destinationPrice'] < $lowest_price['destinationPrice']) {
        $lowest_price = $price;
        $school_external_id = $course_price['code'];
      }
    }

    drupal_alter('kis_pricing_plan_start_date', $lowest_price['startDates'][$start_date_key]);

    $promotion = $lowest_price['startDates'][$start_date_key]['priceRule'];
    $price = new CoursePrice(
      $promotion
        ? $promotion['actualDestinationPrice']
        : $lowest_price['destinationPrice'],
      $lowest_price['destinationCurrency'],
      $promotion
        ? $promotion['actualLocalPrice']
        : $lowest_price['localPrice'],
      $lowest_price['localCurrency'],
      new DateTime($lowest_price['startDates'][$start_date_key]['start']),
      $lowest_price['duration']
    );

    $price->setSchoolCode($school_external_id);

    if ($promotion) {
      $price->setOriginalDestinationPrice($lowest_price['destinationPrice']);
      $price->setOriginalLocalPrice($lowest_price['localPrice']);
      $price->setPromotionCode($promotion['code']);
      $price->setPromotionRuleOperator($promotion['ruleOperator']);
      $price->setPromotionRuleValue($promotion['ruleValue']);
      $price->setPromotionDuration($promotion['duration']);
      $price->setPromotion($promotion['description']);
    }

    return $price;
  }

}
