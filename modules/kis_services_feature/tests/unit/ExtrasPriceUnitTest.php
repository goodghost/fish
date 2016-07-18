<?php

require_once 'kis_services_feature/includes/Price.inc';
require_once 'kis_services_feature/includes/ExtrasPrice.inc';

/**
 * Class ExtrasPriceUnitTest
 * @covers ExtrasPrice::
 */
class ExtrasPriceUnitTest extends PHPUnit_Framework_TestCase {
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
   * @group ExtrasPrice
   * @covers ExtrasPrice::__construct
   */
  public function testCreateExtrasPrice_Construct() {
    // Set up
    $code = 'TLSKI';
    $destination_price = 640;
    $destination_currency = 'USD';
    $local_price = 700;
    $local_currency = 'GBP';

    // Act
    $client = new ExtrasPrice($code, $destination_price, $destination_currency, $local_price, $local_currency);

    // Verify
    $this->assertInstanceOf('ExtrasPrice',$client);

    return $client;
  }

  /**
   * @group ExtrasPrice
   * @covers ExtrasPrice::setCode
   * @covers ExtrasPrice::getCode
   * @depends testCreateExtrasPrice_Construct
   */
  public function testExtrasPrice_GetCode(ExtrasPrice $client) {
    // Set up
    $client->setCode('TLSKI');
    $expected_code = 'TLSKI';

    // Act
    $code = $client->getCode();

    // Verify
    $this->assertEquals($expected_code, $code);

  }

}
