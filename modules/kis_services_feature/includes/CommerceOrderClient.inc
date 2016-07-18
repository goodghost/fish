<?php

/**
 * Class CommerceOrderClient
 */
class CommerceOrderClient extends ServiceClient {
  /**
   * Creates a client with JSON as formatter.
   */
  public function __construct($endpoint, $cache_ttl = 0) {
    parent::__construct($endpoint, $cache_ttl);
  }
}