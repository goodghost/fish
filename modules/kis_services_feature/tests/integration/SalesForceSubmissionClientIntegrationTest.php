<?php


require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/SalesForceSubmissionClient.inc';

/**
 * Class SalesForceSubmissionClientIntegrationTest.
 *
 * @covers SalesForceSubmissionClient::
 */
class SalesForceSubmissionClientIntegrationTest extends PHPUnit_Framework_TestCase {
  /**
   * Set up environment for your test.
   */
  public function setUp() {}

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {}

  /**
   * @group Salesforce
   * @covers SalesForceSubmissionClient::__construct
   */
  public function testSalesForceSubmissionClient_Construct() {
    // Act
    $client = new SalesForceSubmissionClient();

    // Verify
    $this->assertInstanceOf('SalesForceSubmissionClient', $client);

    return $client;
  }

  /**
   * @group Salesforce
   * @covers SalesForceSubmissionClient::createObject
   * @depends testSalesForceSubmissionClient_Construct
   */
  public function testSalesForceSubmissionClient_createObject(SalesForceSubmissionClient $client) {
    // Set up
    $objectType = 'Lead';
    $date = new DateTime('+2 months');
    $sfObject = array(
      'SourceRecordType__c' => '012200000005xw8AAA',
      'Form_Source__c' => 'Drupal',
      'Publication__c' => 'ENG',
      'Lead_Type__c' => 'Contact Us',
      'Study_Where__c' => 'London',
      'Program_Interest__c' => 'OPUS',
      'Preferred_Start_Date__c' => $date->format('Y-m-d'),
      'FirstName' => 'Kaplanius',
      'LastName' => 'von Kaplan',
      'Country__c' => 'a0911000003I9VFAA0',
      'Email' => 'test@example.com',
      'Phone' => '7984561230',
      'Questions_and_Comments__c' => 'Aight? ',
      'Subscribe_to_Promotions__c' => '1',
      'Sitecat_ID__c' => 'DRU-162',
    );

    // Act
    $client->createObject($objectType, $sfObject);

    // Verify if submission was accepted by API
    $this->assertEquals($client->lastResponse->responseCode, 202);
  }

}
