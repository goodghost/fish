<?php

/**
 * @file
 *
 * Good practice example file for defining PHPUnit tests
 */

/**
 * Class GoodModuleExampleTest
 */
class GoodModuleExampleTest extends PHPUnit_Framework_TestCase {
  /**
   * Set up environment for your test.
   */
  public function setUp() {}

  /**
   * Tear down your environment changes done for your test.
   */
  public function tearDown() {}

  /**
   * Example of test that generates successful outcome.
   */
  public function testSucceedingTest() {
    // test to ensure that the object from an fsockopen is valid
    $this->assertTrue(TRUE);
  }
}
