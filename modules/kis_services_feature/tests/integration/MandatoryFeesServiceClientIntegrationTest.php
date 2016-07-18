<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/MandatoryFeesServiceClient.inc';

/**
 * Class MandatoryFeesServiceClientIntegrationTest.
 *
 * @covers MandatoryFeesServiceClient::
 */
class MandatoryFeesServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {
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
   * @group Extras
   * @covers MandatoryFeesServiceClient::__construct
   */
  public function testMandatoryFeesServiceClient_Construct() {
    // Act
    $client = new MandatoryFeesServiceClient();

    // Verify
    $this->assertInstanceOf('MandatoryFeesServiceClient', $client);

    return $client;
  }

  /**
   * @group Extras
   * @covers MandatoryFeesServiceClient::getPrices
   * @covers MandatoryFeesServiceClient::postProcess
   * @depends testMandatoryFeesServiceClient_Construct
   */
  public function testMandatoryFeesServiceClient_GetPrices(MandatoryFeesServiceClient $client) {
    // Set up
    $culture_code = 'en-GB';
    $currency_code = 'GBP';
    $start_date = DateTime::createFromFormat('Y-m-d', '2014-12-21');
    $duration = 2;

    // Act
    $fees = $client->getPrices($culture_code, $currency_code, array(), $start_date, $duration);
    $fee = current(current(current($fees)));

    // Verify
    $this->assertInternalType('array', $fee);
    $this->assertEquals(1, $fee['mandatory']);
    $this->assertGreaterThan(0, $fee['localPrice']);
    $this->assertGreaterThan(0, $fee['destinationPrice']);
    $this->assertEquals($currency_code, $fee['localCurrency']);
  }

}
