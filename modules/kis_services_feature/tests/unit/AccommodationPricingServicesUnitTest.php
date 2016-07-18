<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/Price.inc';
require_once 'kis_services_feature/includes/AccommodationPrice.inc';
require_once 'kis_services_feature/includes/AccommodationPricingServiceClient.inc';

/**
 * Class AccommodationPricingServicesUnitTest
 */
class AccommodationPricingServicesUnitTest extends PHPUnit_Framework_TestCase {
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
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::__construct
   */
  public function testCreateAccommodationPricingService_Construct() {
    // Set up

    // Act
    $client = new AccommodationPricingServiceClient();

    // Verify
    $this->assertInstanceOf('AccommodationPricingServiceClient', $client);

    return $client;
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::setLastCity
   * @covers AccommodationPricingServiceClient::getLastCity
   * @depends testCreateAccommodationPricingService_Construct
   */
  public function testAccommodationPricingService_GetLastCity(AccommodationPricingServiceClient $client) {
    // Set up
    $city = 'London';
    $client->setLastCity($city);

    // Verify
    $this->assertEquals($city, $client->getLastCity());
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::setLastCurrencyCode
   * @covers AccommodationPricingServiceClient::getLastCurrencyCode
   * @depends testCreateAccommodationPricingService_Construct
   */
  public function testAccommodationPricingService_GetLastCurrencyCode(AccommodationPricingServiceClient $client) {
    // Set up
    $currency = 'GBP';
    $client->setLastCurrencyCode($currency);

    // Verify
    $this->assertEquals($currency, $client->getLastCurrencyCode());
  }

  /**
   * @group Accommodations
   * @covers AccommodationPricingServiceClient::setLastDuration
   * @covers AccommodationPricingServiceClient::getLastDuration
   * @depends testCreateAccommodationPricingService_Construct
   */
  public function testAccommodationPricingService_GetLastDuration(AccommodationPricingServiceClient $client) {
    // Set up
    $duration = 2;
    $client->setLastDuration($duration);

    // Verify
    $this->assertEquals($duration, $client->getLastDuration());
  }

}
