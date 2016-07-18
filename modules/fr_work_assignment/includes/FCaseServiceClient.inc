<?php

/**
 * Class FCaseServiceClient
 */
class FCaseServiceClient extends ServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('fr_services_fcase_endpoint', 'http://213.212.70.93/api/fcases');
    }

    if ($cacheTtl === NULL) {
      $cacheTtl = variable_get('fr_services_fcase_cache', 0);
    }

    parent::__construct($endpoint, $cacheTtl);
  }

  /**
   * Get all cases.
   *
   * @return mixed|null
   */
  public function getList() {
    $data = $this->executeGet();

    return $data;
  }

  /**
   * Assign user to a case.
   *
   * @param $caseId
   * @param $userId
   * @return mixed|null
   * @throws ServiceException
   */
  public function assignToUser($caseId, $userId) {
    $readEndpoint = $this->getEndpoint();

    $updateEndpoint = variable_get('fr_services_fcase_update_endpoint', 'http://213.212.70.93/api/update/fcase');
    $this->setEndpoint($updateEndpoint);

    $data = array(
      'id' => (int)$caseId,
      'OwnerID' => is_numeric($userId) ? (int)$userId : NULL,
    );
    $response = $this->executePost($data);

    $this->setEndpoint($readEndpoint);

    return $response;
  }

}
