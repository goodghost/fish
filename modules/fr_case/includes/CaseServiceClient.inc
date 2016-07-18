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
      $endpoint = variable_get('fr_services_case_endpoint', 'http://213.212.70.93/api/case');
    }

    if ($cacheTtl === NULL) {
      $cacheTtl = variable_get('fr_services_case_cache', 0);
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
