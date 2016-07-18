<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/Price.inc';
require_once 'kis_services_feature/includes/PricingServiceClient.inc';
require_once 'kis_services_feature/includes/CoursePricingServiceClient.inc';

/**
 * Class CoursePricingServiceClientIntegrationTest
 */
class CoursePricingServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {
  /**
   * Set up environment for your test.
   */
  public function setUp() {

  }

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {

  }

  /**
   * @group Courses
   * @covers CoursePricingServiceClient::__construct
   */
  public function testCoursePricingServiceClient_Construct() {
    // Set up

    // Act
    $client = new CoursePricingServiceClient();

    // Verify
    $this->assertInstanceOf('CoursePricingServiceClient', $client);

    return $client;
  }

  /**
   * @group Courses
   * @covers CoursePricingServiceClient::getPrices
   * @covers CoursePricingServiceClient::postProcess
   * @depends testCoursePricingServiceClient_Construct
   */
  public function testCoursePricingServiceClient_GetPrices(CoursePricingServiceClient $client) {
    // Set up
    $culture_code = 'en-GB';
    $currency_code = 'GBP';
    $schools = array('LOC');
    $courses = array('ENGGEN');

    $date = new DateTime();
    $date->add(new DateInterval('P2M'));
    $duration = 2;

    // Act
    $pricing_data = $client->getPrices($culture_code, $currency_code, $schools, $courses, $date, $duration);

    // Verify Return Type is Array
    $this->assertInternalType('array', $pricing_data);
  }

}
