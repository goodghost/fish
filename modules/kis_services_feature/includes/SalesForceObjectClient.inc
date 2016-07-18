<?php

/**
 * Class SalesForceObjectClient
 */
class SalesForceObjectClient extends ServiceClient {
  /**
   * Service constructor. Creates a client with JSON as formatter.
   *
   * @param $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint = NULL, $cache_ttl = NULL, $access_key = NULL, $access_token = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('kis_salesforce_object_endpoint');
    }

    if ($cache_ttl === NULL) {
      $cache_ttl = variable_get('kis_services_salesforce_object_service_cache', 3600);
    }

    parent::__construct($endpoint, $cache_ttl, $access_key, $access_token);
  }

  /**
   * Get salesforce object by its name.
   *
   * @param string $currency_from
   *   Name of SalesForce object.
   *
   * @return array
   *   SalesForce object data.
   */
  public function getObject($object_name) {
    try {
      $path = $object_name;

      if ($data = $this->get($path)) {
        return $data;
      }
    }
    catch (HttpClientException $e) {
      throw $e;
    }
  }

  /**
   * Get lists of available SF objects
   *
   * @return array
   *   SalesForce objects data.
   */
  public function getGlobalObjects() {
    try {
      if ($data = $this->get('globalobjects')) {
        return $data;
      }
    }
    catch (HttpClientException $e) {
      throw $e;
    }
  }

}
