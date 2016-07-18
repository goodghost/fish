<?php

/**
 * Class PrintRequestClient.
 */
class PrintRequestClient extends ServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   */
  public function __construct($endpoint = NULL) {
    parent::__construct($endpoint, 0);
  }

  /**
   * Create print request.
   *
   * @param array $data
   *   Form data.
   *
   * @return mixed|null
   */
  public function create($data) {
    $endpoint = variable_get('fr_services_print_request_create_endpoint', 'http://213.212.70.93/api/request/submit');
    $this->setEndpoint($endpoint);

    $data = $this->executePost($data);
    return $data;
  }

  /**
   * Update print request.
   *
   * @param array $data
   *   Form data.
   *
   * @return mixed|null
   */
  public function update($data) {
    $endpoint = variable_get('fr_services_print_request_update_endpoint', 'http://213.212.70.93/api/request/update');
    $this->setEndpoint($endpoint);

    $data = $this->executePost($data);
    return $data;
  }

  /**
   * Approve print request.
   */
  public function approve($printRequestId) {
    $endpoint = variable_get('fr_services_print_request_update_endpoint', 'http://213.212.70.93/api/request/update');
    $this->setEndpoint($endpoint);

    $data = array(
      'id' => $printRequestId,
      'status' => FR_PRINT_REQUEST_STATUS_APPROVED,
    );

    $data = $this->executePost($data);
    return $data;
  }

  /**
   * Reject print request.
   */
  public function reject($printRequestId, $reason) {
    $endpoint = variable_get('fr_services_print_request_update_endpoint', 'http://213.212.70.93/api/request/update');
    $this->setEndpoint($endpoint);

    $data = array(
      'id' => $printRequestId,
      'status' => FR_PRINT_REQUEST_STATUS_REJECTED,
      'Reject Reason' => $reason,
    );

    $data = $this->executePost($data);
    return $data;
  }

}
