<?php

require_once 'fr_tests/Mocks.php';
require_once 'fr_work_assignment/includes/FCaseServiceClient.inc';

/**
 * Class FCaseServiceClientIntegrationTest
 *
 * @covers ServiceClient
 * @covers FCaseServiceClient
 */
class FCaseServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {

  // Case ID
  private static $caseId = 110;

  // Case Docket
  private static $caseDocket = 0;

  /**
   * @group DataSet
   * @covers FCaseServiceClient::__construct
   */
  public function testFCaseServiceClient_Construct() {
    $client = new FCaseServiceClient();
    $this->assertInstanceOf('FCaseServiceClient', $client);
    return $client;
  }

  /**
   * @group DataSet
   * @covers FCaseServiceClient::getList
   * @depends testFCaseServiceClient_Construct
   */
  public function testFCaseServiceClient_GetList(FCaseServiceClient $client) {
    $data = $client->getList(self::$caseId);

    // Verify

    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['cases']);
    $this->assertInternalType('array', $data['cases'][0]);

    $this->assertInternalType('int', $data['cases'][0]['id']);
    $this->assertInternalType('string', $data['cases'][0]['Case ID']);
    $this->assertInternalType('string', $data['cases'][0]['Case Reference']);
    $this->assertInternalType('string', $data['cases'][0]['Case Status']);
    $this->assertInternalType('string', $data['cases'][0]['Team']);
    $this->assertInternalType('int', $data['cases'][0]['TeamID']);
    $this->assertInternalType('string', $data['cases'][0]['Owner']);
    $this->assertInternalType('int', $data['cases'][0]['OwnerID']);
    $this->assertInternalType('int', $data['cases'][0]['Priority']);
    $this->assertInternalType('string', $data['cases'][0]['Case Date']);
    $this->assertInternalType('string', $data['cases'][0]['Target Date']);
    $this->assertInternalType('string', $data['cases'][0]['Retailer']);
  }

}
