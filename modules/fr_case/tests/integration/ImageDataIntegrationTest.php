<?php

require_once 'fr_tests/Mocks.php';
require_once 'fr_case/includes/ImageDataServiceClient.inc';

/**
 * Class ImageDataServiceClientIntegrationTest
 *
 * @covers ServiceClient
 * @covers ImageDataServiceClient
 */
class ImageDataServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {

  // Image ID
  private static $imageId = 56;

  /**
   * @group DataSet
   * @covers ImageDataServiceClient::__construct
   */
  public function testImageDataServiceClient_Construct() {
    $client = new ImageDataServiceClient();
    $this->assertInstanceOf('ImageDataServiceClient', $client);
    return $client;
  }

  /**
   * @group DataSet
   * @covers ImageDataServiceClient::getImageDataById
   * @depends testImageDataServiceClient_Construct
   */
  public function testImageDataServiceClient_GetImageDataById(ImageDataServiceClient $client) {
    $data = $client->getImageDataById(self::$imageId);

    // Verify

    $this->assertInternalType('array', $data);
    $this->assertInternalType('array', $data['imagedata']);
    $this->assertInternalType('array', $data['imagedata']['exif']);
    $this->assertInternalType('array', $data['imagedata']['notes']);
  }

}
