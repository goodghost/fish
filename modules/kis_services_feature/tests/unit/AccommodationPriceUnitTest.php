<?php

require_once("kis_services_feature/includes/Price.inc");
require_once("kis_services_feature/includes/AccommodationPrice.inc");

/**
 * Class AccommodationPriceUnitTest
 * @covers AccommodationPrice::
 */
class AccommodationPriceUnitTest extends PHPUnit_Framework_TestCase {
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
   * @covers AccommodationPrice::__construct
   * @covers AccommodationPrice::setCode
   * @covers AccommodationPrice::setDuration
   */
  public function testAccommodationPrice_Construct() {
    // Set up
    $code = 'TLSKI';
    $duration = 2;
    $destination_price = 640;
    $destination_currency = 'USD';
    $local_price = 700;
    $local_currency = 'GBP';

    // Act
    $accommodationPrice = new AccommodationPrice($code, $duration, $destination_price, $destination_currency, $local_price, $local_currency, 1);

    // Verify
    $this->assertInstanceOf('AccommodationPrice', $accommodationPrice);

    return $accommodationPrice;
  }

  /**
   * @group Accommodations
   * @covers AccommodationPrice::getCode
   * @depends testAccommodationPrice_Construct
   */
  public function testAccommodationPrice_GetCode(AccommodationPrice $accommodationPrice) {
    // Set up
    $expected_code = 'TLSKI';

    // Verify Property
    $this->assertObjectHasAttribute('code', $accommodationPrice);

    // Verify Property
    $this->assertEquals($expected_code, $accommodationPrice->getCode());

  }

  /**
   * @group Accommodations
   * @covers AccommodationPrice
   * @covers AccommodationPrice::getDuration
   * @depends testAccommodationPrice_Construct
   */
  public function testAccommodationPrice_GetDuration(AccommodationPrice $accommodationPrice) {
    // Set up
    $expected_duration = 2;

    // Verify Property
    $this->assertObjectHasAttribute('duration', $accommodationPrice);

    // Verify Property
    $this->assertEquals($expected_duration, $accommodationPrice->getDuration());
  }

}
