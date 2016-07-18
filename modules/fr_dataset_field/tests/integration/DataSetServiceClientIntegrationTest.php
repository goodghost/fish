<?php

require_once 'fr_tests/Mocks.php';
require_once 'fr_dataset_field/includes/DataSetServiceClient.inc';

/**
 * Class DataSetServiceClientIntegrationTest
 *
 * @covers ServiceClient
 * @covers DataSetServiceClient
 */
class DataSetServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {

  // Dataset
  private static $dataset = 'album_print_queue';

  // Fields
  private static $fields = array(
    array('field' => 'id', 'type' => 'int'),
    array('field' => 'delivery_address', 'type' => 'string'),
  );

  // Filters
  private static $filters = array(
    array('field' => 'id', 'operator' => '>=', 'value' => 2),
    array('field' => 'delivery_address', 'operator' => '!=', 'value' => 'ew'),
    array('field' => 'case_id', 'operator' => '<', 'value' => 100),
  );

  // Sorting
  private static $sorting = 'id';

  /**
   * @group DataSet
   * @covers DataSetServiceClient::__construct
   */
  public function testDataSetServiceClient_Construct() {
    $client = new DataSetServiceClient();
    $this->assertInstanceOf('DataSetServiceClient', $client);
    return $client;
  }

  /**
   * @group DataSet
   * @covers DataSetServiceClient::getList
   * @depends testDataSetServiceClient_Construct
   */
  public function testDataSetServiceClient_GetList(DataSetServiceClient $client) {
    $data = $client->getList();

    // Verify
    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['datasets']);
    $this->assertInternalType('array', $data['datasets'][0]);
    $this->assertInternalType('string', $data['datasets'][0]['id']);
    $this->assertInternalType('string', $data['datasets'][0]['name']);
  }

  /**
   * @group DataSet
   * @covers DataSetServiceClient::getStructure
   * @depends testDataSetServiceClient_Construct
   */
  public function testDataSetServiceClient_GetStructure(DataSetServiceClient $client) {
    $data = $client->getStructure(self::$dataset);

    // Verify
    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['fields']);
    $this->assertInternalType('array', $data['fields'][0]);
    $this->assertInternalType('string', $data['fields'][0]['name']);
    $this->assertInternalType('string', $data['fields'][0]['type']);
  }

  /**
   * Test data without filters.
   *
   * @group DataSet
   * @covers DataSetServiceClient::getData
   * @covers DataSetServiceClient::setLimit
   * @depends testDataSetServiceClient_Construct
   */
  public function testDataSetServiceClient_GetDataNoFilters(DataSetServiceClient $client) {
    $client->setLimit(1);
    $data = $client->getData(self::$dataset);

    // Verify
    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['result']);
    $this->assertInternalType('array', $data['result'][0]);
    $this->assertInternalType(self::$fields[0]['type'], $data['result'][0][self::$fields[0]['field']]);
    $this->assertInternalType(self::$fields[1]['type'], $data['result'][0][self::$fields[1]['field']]);
  }

  /**
   * Test dataset with applied filters.
   *
   * @group DataSet
   * @covers DataSetServiceClient::getData
   * @covers DataSetServiceClient::setFilters
   * @covers DataSetServiceClient::setLimit
   * @depends testDataSetServiceClient_Construct
   */
  public function testDataSetServiceClient_GetDataWithFilters(DataSetServiceClient $client) {
    $client->setFilters(self::$filters);
    $data = $client->getData(self::$dataset);

    // Verify
    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['result']);
    $this->assertInternalType('array', $data['result'][0]);

    foreach (self::$filters as $filter) {
      switch ($filter['operator']) {
        case '=':
          $this->assertEquals($data['result'][0][$filter['field']], $filter['value']);
          break;
        case '>':
          $this->assertGreaterThan($filter['value'], $data['result'][0][$filter['field']]);
          break;
        case '>=':
          $this->assertGreaterThanOrEqual($filter['value'], $data['result'][0][$filter['field']]);
          break;
        case '<':
          $this->assertLessThan($filter['value'], $data['result'][0][$filter['field']]);
          break;
        case '<=':
          $this->assertLessThanOrEqual($filter['value'], $data['result'][0][$filter['field']]);
          break;
      }
    }
  }

  /**
   * Test dataset with sorting.
   *
   * @group DataSet
   * @covers DataSetServiceClient::getData
   * @covers DataSetServiceClient::setSorting
   * @covers DataSetServiceClient::setOrder
   * @covers DataSetServiceClient::setLimit
   * @depends testDataSetServiceClient_Construct
   */
  public function testDataSetServiceClient_GetDataWithSorting(DataSetServiceClient $client) {
    $client->setSorting(self::$sorting);
    $client->setOrder('asc');
    $client->setLimit(1);
    $data = $client->getData(self::$dataset);

    $client->setOrder('desc');
    $data_inverted = $client->getData(self::$dataset);

    // Verify
    $this->assertNotEquals($data, $data_inverted);
  }

}
