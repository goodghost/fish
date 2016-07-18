<?php

/**
 * Class SalesForceSubmissionClient
 */
class SalesForceSubmissionClient extends ServiceClient {
  /**
   * Service constructor. Creates a client with JSON as formatter.
   *
   * @param $endpoint
   */
  public function __construct($endpoint = NULL, $cache_ttl = NULL, $access_key = NULL, $access_token = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('kis_salesforce_submission_endpoint');
    }

    parent::__construct($endpoint, $cache_ttl, $access_key, $access_token);
  }

  /**
   * Crates SalesForce object.
   *
   * @param string $object_type
   * @param array $sf_object
   */
  public function createObject($object_type, $sf_object) {
    // Add object type to the end of endpoint URL.
    $this->setEndpoint($this->getEndpoint() . '/' . $object_type);

    if ($data = $this->post(array($sf_object), array())) {
      return $data;
    }
  }
}
