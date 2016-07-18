<?php

require_once 'kis_services_feature/tests/Mocks.php';
require_once 'kis_services_feature/includes/BlogPost.inc';
require_once 'kis_services_feature/includes/BlogServiceClient.inc';

/**
 * Class BlogServiceClientIntegrationTest
 *
 * @covers BlogPost::
 * @covers BlogServiceClient::
 */
class BlogServiceClientIntegrationTest extends PHPUnit_Framework_TestCase {
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
   * @group Blog
   * @covers BlogServiceClient::__construct
   */
  public function testBlogServiceClient_Construct() {
    // Set up
    $endpoint = variable_get('blog_endpoint');

    // Act
    $client = new BlogServiceClient($endpoint);

    // Verify
    $this->assertInstanceOf('BlogServiceClient', $client);

    return $client;
  }

  /**
   * @group Blog
   * @covers BlogServiceClient::get
   * @covers BlogServiceClient::postProcess
   * @covers BlogPost::__construct
   * @depends testBlogServiceClient_Construct
   */
  public function testBlogServiceClient_Get(BlogServiceClient $client) {
    // Set up

    // Act
    $data = $client->get('blog/api/get_recent_posts/');

    // Verify Return Type is Array
    $this->assertInternalType('array', $data);

    // Verify Return Type is array of BlogPost objects
    $blog_post = array_shift($data);
    $this->assertInstanceOf('BlogPost', $blog_post);
  }

}
