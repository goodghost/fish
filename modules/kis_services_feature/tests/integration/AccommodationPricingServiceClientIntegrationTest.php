<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/Price.inc';
require_once 'kis_services_feature/includes/AccommodationPrice.inc';
require_once 'kis_services_feature/includes/AccommodationPricingServiceClient.inc';

/**
 * Class AccommodationPricingServiceClientIntegrationTest.
 *
 * @covers AccommodationPricingServiceClient::
 */
class AccommodationPricingServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {
  private $city, $start_date, $duration, $currency_code, $culture_code;

  /**
   * Set up environment for your test.
   */
  public function setUp() {
    $this->city = 'London';
    $this->start_date = new DateTime('+2 months');
    $this->duration = 2;
    $this->currency_code = 'GBP';
    $this->culture_code = 'en-GB';
  }

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {}

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::__construct
   */
  public function testCreateAccommodationPricingService_Construct() {
    // Act
    $client = new AccommodationPricingServiceClient();

    // Verify
    $this->assertInstanceOf('AccommodationPricingServiceClient', $client);

    return $client;
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::getPrices
   * @covers AccommodationPricingServiceClient::postProcess
   * @depends testCreateAccommodationPricingService_Construct
   */
  public function testAccommodationPricingService_GetPrices(AccommodationPricingServiceClient $client) {
    // Act
    $price_objects = $client->getPrices($this->city, $this->start_date, $this->duration, $this->currency_code, $this->culture_code);

    // Verify Return Type is Array
    $this->assertInternalType('array', $price_objects);

    // Verify Return Type is array of AccommodationPrice objects
    $accomodation_price = array_shift($price_objects);
    $this->assertInstanceOf('AccommodationPrice', $accomodation_price);

    return $client;
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::setLastCity
   * @covers AccommodationPricingServiceClient::getLastCity
   * @depends testAccommodationPricingService_GetPrices
   */
  public function testAccommodationPricingService_GetLastCity(AccommodationPricingServiceClient $client) {
    // Verify
    $this->assertEquals($this->city, $client->getLastCity());
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::setLastCurrencyCode
   * @covers AccommodationPricingServiceClient::getLastCurrencyCode
   * @depends testAccommodationPricingService_GetPrices
   */
  public function testAccommodationPricingService_GetLastCurrencyCode(AccommodationPricingServiceClient $client) {
    // Verify
    $this->assertEquals($this->currency_code, $client->getLastCurrencyCode());
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::setLastDuration
   * @covers AccommodationPricingServiceClient::getLastDuration
   * @depends testAccommodationPricingService_GetPrices
   */
  public function testAccommodationPricingService_GetLastDuration(AccommodationPricingServiceClient $client) {
    // Verify
    $this->assertEquals($this->duration, $client->getLastDuration());
  }

}
