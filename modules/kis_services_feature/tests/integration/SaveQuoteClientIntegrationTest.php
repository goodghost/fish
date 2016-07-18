<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/Quote.inc';
require_once 'kis_services_feature/includes/SaveQuoteClient.inc';

/**
 * Class SaveQuoteClientIntegrationTest
 *
 * @covers SaveQuoteClient::
 */
class SaveQuoteClientIntegrationTest extends PHPUnit_Framework_TestCase {
  /**
   * Set up environment for your test.
   */
  public function setUp() {}

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {}

  /**
   * @group Quote
   * @covers SaveQuoteClient::__construct
   */
  public function testSaveQuoteClient_Construct() {
    // Set up
    $endpoint = variable_get('kis_save_quote_endpoint');

    // Act
    $client = new SaveQuoteClient($endpoint);

    // Verify
    $this->assertInstanceOf('SaveQuoteClient', $client);

    return $client;
  }

  /**
   * @group Quote
   * @covers SaveQuoteClient::saveQuote
   * @depends testSaveQuoteClient_Construct
   */
  public function testSaveQuoteClient_saveQuote(SaveQuoteClient $client) {
    // Set up
    $quoteData = array(
      'bookingType'=> 'quote',
      'schoolId' => 'CHG',
      'localCurrencyCode'=> 'GBP',
      'market' => 'en-GB',
      'total'=> '2460',
      'externalReference' => '6406',
      'course'=> array(
        'code' => 'ENGVAC',
        'duration'=> '4',
        'startDate' => '2016-01-25T12:00:00Z',
        'localPrice'=> '925.69',
        'destinationPrice' => '1460',
        'priceRule'=> '',
        'translations' => array(
          'key'=> 'courseDescription',
          'value' => 'Vacation English',
        )
      ),
      'extras'=> array(),
      'accommodation' => array(
        'code'=> 'LSHYSH',
        'destinationPrice' => '1000',
        'localPrice'=> '634.04',
        'accommodationType' => 'Homestay',
        'accommodationConfirmed'=> '1',
        'priceRule' => '',
        'translations' => array(
          'key' => 'accommodationTypeDescription',
          'value'=> 'Homestay',
        )
      ),
      'personalData' => array(
        'firstName'=> 'Kaplant',
        'surname' => 'Kaplansky',
        'gender'=> '',
        'dateOfBirth' => '',
        'nationality'=> '',
        'addressLine1' => '',
        'addressLine2'=> '',
        'city' => '',
        'postCode'=> '',
        'county' => '',
        'country'=> 'GB',
        'phoneNumber' => '079456123456',
        'email'=> 'kaplant@example.com',
        'termsConfirmation' => '1',
        'shareData'=> ''
      ),
      'bankTransferData' => '',
      'paymentResult'=> '',
      'translations' => array(
        'key'=> 'schoolDescription',
        'value' => 'Chicago - Illinois Institute of Technology',
      ),
    );

    // Act
    $quoteObject = new Quote($quoteData['bookingType'], $quoteData['externalReference'], $quoteData['schoolId'], $quoteData['market'], $quoteData['localCurrencyCode'], $quoteData['total']);
    $quoteObject->course = (object) $quoteData['course'];
    $quoteObject->extras = $quoteData['extras'];
    $quoteObject->accommodation = (object) $quoteData['accommodation'];
    $quoteObject->personalData = (object) $quoteData['personalData'];
    $quoteObject->bankTransferData = $quoteData['bankTransferData'];
    $quoteObject->paymentResult = $quoteData['paymentResult'];
    $quoteObject->translations = $quoteData['translations'];

    $client->saveQuote($quoteObject);

    // Verify if quote was accepted by API
    $this->assertEquals($client->lastResponse->responseCode, 202);
  }

}
