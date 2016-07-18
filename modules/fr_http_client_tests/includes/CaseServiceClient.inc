<?php

/**
 * Class CaseServiceClient
 */
class CaseServiceClient extends ServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = 'http://requestb.in/1m77sa41';
    }

    if ($cacheTtl === NULL) {
      $cacheTtl = 0;
    }

    parent::__construct($endpoint, $cacheTtl);
  }

  /**
   * Get case by id.
   *
   * @param $caseId
   *
   * @return mixed|null
   */
  public function getCaseById($caseId) {
    $caseId = HttpClient::urlencode_rfc3986($caseId);
    $data = $this->executeGet($caseId);

    return $data;
  }


  public function getMyData() {
    $data = $this->executeGet();
    return $data;
  }

  /**
   * Get scene dockets.
   *
   * @param $caseId
   * @param $sceneId
   *
   * @return mixed|null
   */
  public function getSceneDockets($caseId, $sceneId) {
    $caseId = HttpClient::urlencode_rfc3986($caseId);
    $sceneId = HttpClient::urlencode_rfc3986($sceneId);
    $data = $this->executeGet("$caseId/$sceneId");

    return $data;
  }

}
