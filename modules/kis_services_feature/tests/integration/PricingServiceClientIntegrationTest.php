<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/Price.inc';
require_once 'kis_services_feature/includes/PricingServiceClient.inc';
require_once 'kis_services_feature/includes/CoursePrice.inc';
require_once 'kis_pricing_plan/kis_pricing_plan.module';


/**
 * Class PricingServiceClientIntegrationTest.
 */
class PricingServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {
  private $culture_code, $currency_code, $schools, $courses, $start_date, $duration;

  /**
   * Set up environment for your test.
   */
  public function setUp() {
    $this->culture_code = 'en-GB';
    $this->currency_code = 'GBP';
    $this->schools = array('LOC');
    $this->courses = array('ENGGEN');
    $this->start_date = new DateTime('+2 months');
    $this->duration = 2;
  }

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {}

  /**
   * @group PricingServiceClient
   * @covers PricingServiceClient::__construct
   */
  public function testCreatePricingServiceClient_Construct() {
    // Act
    $client = new PricingServiceClient();

    // Verify
    $this->assertInstanceOf('ServiceClient', $client);
    $this->assertInstanceOf('PricingServiceClient', $client);

    return $client;
  }

  /**
   * @group PricingServiceClient
   * @covers PricingServiceClient::getPrices
   * @depends testCreatePricingServiceClient_Construct
   */
  public function testPricingService_GetPrices(PricingServiceClient $client) {
    // Act
    $prices = $client->getPrices($this->culture_code, $this->currency_code, $this->schools, $this->courses, $this->start_date, $this->duration);
    $price = $prices[0];

    // Verify
    $this->assertInternalType('array', $prices);
    $this->assertArrayHasKey('code', $price);
    $this->assertArrayHasKey('schoolName', $price);
    $this->assertArrayHasKey('classDb', $price);
    $this->assertArrayHasKey('courses', $price);

    return $prices;
  }

  /**
   * @group PricingServiceClient
   * @covers kis_pricing_plan_process_pricing_display
   * @depends testPricingService_GetPrices
   */
  public function testPricingService_Display(Array $prices) {
    $coursePrice = @kis_pricing_plan_process_pricing_display(0, $prices[0]['courses'][0]['prices'][0]);

    // Verify
    $this->assertInstanceOf('CoursePrice', $coursePrice);
    $this->assertGreaterThan(0, $coursePrice->getLocalPrice());
    $this->assertGreaterThan(0, $coursePrice->getDestinationPrice());
    $this->assertEquals($this->duration, $coursePrice->getDuration());
    $this->assertEquals($this->currency_code, $coursePrice->getLocalCurrency());
    $this->assertEquals($this->currency_code, $coursePrice->getDestinationCurrency());
    $this->assertEquals($this->schools[0], $prices[0]['code']);
    $this->assertEquals($this->courses[0], $prices[0]['courses'][0]['code']);

    return $coursePrice;
  }

}
