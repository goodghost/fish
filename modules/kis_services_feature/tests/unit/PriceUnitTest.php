<?php

require_once 'kis_services_feature/includes/Price.inc';

/**
 * Class PriceUnitTest.
 *
 * @covers Price::
 */
class PriceUnitTest extends PHPUnit_Framework_TestCase {
  private $destination_price = 640;
  private $destination_currency = 'GBP';
  private $local_price = 740;
  private $local_currency = 'USD';

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
   * @group Price
   * @covers Price::__construct
   * @covers Price::setDestinationCurrency
   * @covers Price::setDestinationPrice
   * @covers Price::setLocalCurrency
   * @covers Price::setLocalPrice
   */
  public function testPrice_Construct() {
    // Act
    $client = new Price($this->destination_price, $this->destination_currency, $this->local_price, $this->local_currency);

    // Verify
    $this->assertInstanceOf('Price', $client);

    return $client;
  }

  /**
   * @group Price
   * @covers Price::getDestinationCurrency
   * @depends testPrice_Construct
   */
  public function testAccommodationPricingService_GetDestinationCurrency(Price $price) {
    // Act
    $returned_destination_currency = $price->getDestinationCurrency();

    // Verify
    $this->assertEquals($this->destination_currency, $returned_destination_currency);
  }

  /**
   * @group Price
   * @covers Price::getDestinationPrice
   * @depends testPrice_Construct
   */
  public function testAccommodationPricingService_GetDestinationPrice(Price $price) {
    // Act
    $returned_destination_price = $price->getDestinationPrice();

    // Verify
    $this->assertEquals($this->destination_price, $returned_destination_price);
  }


  /**
   * @group Price
   * @covers Price::getLocalCurrency
   * @depends testPrice_Construct
   */
  public function testAccommodationPricingService_GetLocalCurrency(Price $price) {
    // Act
    $returned_local_currency = $price->getLocalCurrency();

    // Verify
    $this->assertEquals($this->local_currency, $returned_local_currency);
  }

  /**
   * @group Price
   * @covers Price::getLocalPrice
   * @depends testPrice_Construct
   */
  public function testAccommodationPricingService_GetLocalPrice(Price $price) {
    // Act
    $returned_destination_price = $price->getLocalPrice();

    // Verify
    $this->assertEquals($this->local_price, $returned_destination_price);
  }

  /**
   * @group Price
   * @covers Price::mergePrices
   * @depends testPrice_Construct
   */
  public function testAccommodationPricingService_MergePrices(Price $price) {
    // Set up
    $destination_price = 1000;
    $destination_currency = 'GBP';
    $local_price = 1000;
    $local_currency = 'USD';

    // Act
    $price_to_merge_with = new Price($destination_price, $destination_currency, $local_price, $local_currency);
    $price->mergePrices($price_to_merge_with);

    // Verify
    $this->assertEquals($destination_price + $this->destination_price, $price->getDestinationPrice());
    $this->assertEquals($local_price + $this->local_price, $price->getLocalPrice());
  }

}
