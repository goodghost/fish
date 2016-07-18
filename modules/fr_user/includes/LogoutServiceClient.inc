<?php

/**
 * Class LogoutServiceClient
 */
class LogoutServiceClient extends ServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('fr_services_logout_endpoint', 'http://213.212.70.93/api/logout');
    }

    parent::__construct($endpoint, 0);
  }


  /**
   * Logout user from LDAP.
   *
   * @return mixed|null
   */
  public function logout() {
    return $this->executeGet();
  }

}
