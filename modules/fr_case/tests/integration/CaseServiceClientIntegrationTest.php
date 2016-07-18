<?php

require_once 'fr_tests/Mocks.php';
require_once 'fr_case/includes/CaseServiceClient.inc';

/**
 * Class CaseServiceClientIntegrationTest
 *
 * @covers ServiceClient
 * @covers CaseServiceClient
 */
class CaseServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {

  // Case ID
  private static $caseId = 110;

  // Case Docket
  private static $caseDocket = 0;

  /**
   * @group DataSet
   * @covers CaseServiceClient::__construct
   */
  public function testCaseServiceClient_Construct() {
    $client = new CaseServiceClient();
    $this->assertInstanceOf('CaseServiceClient', $client);
    return $client;
  }

  /**
   * @group DataSet
   * @covers CaseServiceClient::getCaseById
   * @depends testCaseServiceClient_Construct
   */
  public function testCaseServiceClient_GetCaseById(CaseServiceClient $client) {
    $data = $client->getCaseById(self::$caseId);

    // Verify

    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['casedetails']);
    $this->assertInternalType('array', $data['casedetails'][0]);

    $this->assertInternalType('int', $data['casedetails'][0]['case_id']);
    $this->assertInternalType('string', $data['casedetails'][0]['reference']);
    $this->assertInternalType('int', $data['casedetails'][0]['num_exhibits']);
    $this->assertInternalType('string', $data['casedetails'][0]['case_owner']);
    $this->assertInternalType('int', $data['casedetails'][0]['case_owner_id']);
    $this->assertInternalType('string', $data['casedetails'][0]['case_date']);
    $this->assertInternalType('string', $data['casedetails'][0]['case_type']);
    $this->assertInternalType('int', $data['casedetails'][0]['case_scenes']);
    $this->assertInternalType('string', $data['casedetails'][0]['gpms_status']);

    $this->assertInternalType('array', $data['casedetails'][0]['scenes']);

    $this->assertEquals($data['casedetails'][0]['case_id'], self::$caseId);
    $this->assertTrue(!isset($data['casedetails'][1]));
  }

  /**
   * @group DataSet
   * @covers CaseServiceClient::getSceneDockets
   * @depends testCaseServiceClient_Construct
   */
  public function testCaseServiceClient_GetSceneDockets(CaseServiceClient $client) {
    $data = $client->getSceneDockets(self::$caseId, self::$caseDocket);

    // Verify

    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['scenedetails']);

    $docket = reset($data['scenedetails']);
    $this->assertInternalType('array', $docket);
    $this->assertInternalType('array', $docket[0]);

    $this->assertInternalType('int', $docket[0]['id']);
    $this->assertInternalType('int', $docket[0]['category']);
    $this->assertInternalType('int', $docket[0]['order']);
    $this->assertInternalType('string', $docket[0]['user_id']);
    $this->assertInternalType('string', $docket[0]['ref']);
    $this->assertInternalType('string', $docket[0]['type']);
    $this->assertInternalType('string', $docket[0]['exttype']);
    $this->assertInternalType('string', $docket[0]['thumbnail']);
    $this->assertInternalType('string', $docket[0]['screensize']);
    $this->assertInternalType('string', $docket[0]['fullsize']);
    $this->assertInternalType('bool', $docket[0]['sensitive']);
    $this->assertInternalType('bool', $docket[0]['restricted']);
  }

}
