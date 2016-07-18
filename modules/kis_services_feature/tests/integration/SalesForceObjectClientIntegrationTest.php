<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/SalesForceObjectClient.inc';

/**
 * Class SalesForceObjectClientIntegrationTest.
 *
 * @covers SalesForceObjectClient::
 */
class SalesForceObjectClientIntegrationTest extends PHPUnit_Framework_TestCase {
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
   * @covers SalesForceObjectClient::__construct
   */
  public function testSalesForceObjectClient_Construct() {
    // Act
    $client = new SalesForceObjectClient();

    // Verify
    $this->assertInstanceOf('SalesForceObjectClient', $client);

    return $client;
  }

  /**
   * @group Salesforce
   * @covers SalesForceObjectClient::getGlobalObjects
   * @depends testSalesForceObjectClient_Construct
   */
  public function testSalesForceObjectClient_getGlobalObjects(SalesForceObjectClient $client) {
    // Act
    $globalObjects = $client->getGlobalObjects();

    // Verify Return Type is Array
    $this->assertInternalType('array', $globalObjects);

    // Verify if global Salesforce objects includes objects
    $this->assertArrayHasKey('sobjects', $globalObjects);
  }

  /**
   * @group Salesforce
   * @covers SalesForceObjectClient::getObject
   * @depends testSalesForceObjectClient_Construct
   */
  public function testSalesForceObjectClient_getObject(SalesForceObjectClient $client) {
    // Act
    $leadObject = $client->getObject('Lead');

    // Verify Return Type is Array
    $this->assertInternalType('array', $leadObject);

    // Verify if global Salesforce objects includes objects
    $this->assertEquals('Lead', $leadObject['name']);
  }

}
