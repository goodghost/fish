<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/Price.inc';
require_once 'kis_services_feature/includes/ExtrasPrice.inc';
require_once 'kis_services_feature/includes/ExtrasPricingServiceClient.inc';

/**
 * Class ExtrasPricingServiceClientIntegrationTest.
 *
 * @covers ExtrasPricingServiceClient::
 */
class ExtrasPricingServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {
  private $city, $culture_code, $currency_code, $start_date, $duration;

  /**
   * Set up environment for your test.
   */
  public function setUp() {
    $this->city = 'London';
    $this->culture_code = 'en-US';
    $this->currency_code = 'USD';
    $this->start_date = new DateTime('+2 months');
    $this->duration = 2;
  }

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {}

  /**
   * @group Extras
   * @covers ExtrasPricingServiceClient::__construct
   */
  public function testExtrasPricingServiceClientService_Construct() {
    // Set up
    $endpoint = variable_get('kis_extras_pricing_endpoint');

    // Act
    $client = new ExtrasPricingServiceClient($endpoint);

    // Verify
    $this->assertInstanceOf('ExtrasPricingServiceClient', $client);

    return $client;

  }

  /**
   * @group Extras
   * @covers ExtrasPricingServiceClient::getPrices
   * @covers ExtrasPricingServiceClient::postProcess
   * @depends testExtrasPricingServiceClientService_Construct
   */
  public function testExtrasPricingServiceClientService_GetPrices(ExtrasPricingServiceClient $client) {
    // Act
    // Example call: http://kictestapi.eu.cloudhub.io/api/extras/London/USD/en-US?courseStartDate=2014-04-07&courseDuration=2&access_token=kicbus
    $prices = $client->getPrices($this->city, $this->culture_code, $this->currency_code, $this->start_date, $this->duration);
    $price = current($prices);

    // Verify
    $this->assertInstanceOf('ExtrasPrice', $price);
    $this->assertInternalType('array', $prices);

    $this->assertGreaterThan(0, $price->getLocalPrice());
    $this->assertGreaterThan(0, $price->getDestinationPrice());

    $this->assertEmpty($price->getMandatory());

    $this->assertEquals($this->currency_code, $price->getLocalCurrency());
    $this->assertEquals('GBP', $price->getDestinationCurrency());
  }

}
