<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/CurrencyExchangeClient.inc';

/**
 * Class CurrencyExchangeClientIntegrationTest.
 *
 * @covers CurrencyExchangeClient::
 */
class CurrencyExchangeClientIntegrationTest extends PHPUnit_Framework_TestCase {
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
   * @group Currency
   * @covers CurrencyExchangeClient::__construct
   */
  public function testCurrencyExchangeClient_Construct() {
    // Set up

    // Act
    $client = new CurrencyExchangeClient();

    // Verify
    $this->assertInstanceOf('CurrencyExchangeClient', $client);

    return $client;

  }

  /**
   * @group Currency
   * @covers CurrencyExchangeClient::exchange
   * @depends testCurrencyExchangeClient_Construct
   */
  public function testCurrencyExchangeClient_Exchange(CurrencyExchangeClient $client) {
    // Set up
    $currency_from = 'GBP';
    $currency_to = 'USD';
    $amount = 100;

    // Act
    $conversion = $client->exchange($currency_from, $currency_to, $amount);

    // Verify Return Type is Float
    $this->assertInternalType('float', $conversion);

    // Verify if value in USD currency is always bigger than value in GBP
    $this->assertGreaterThan($amount, $conversion);
  }

}
