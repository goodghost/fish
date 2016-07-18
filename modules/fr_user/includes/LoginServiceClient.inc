<?php

/**
 * Class LoginServiceClient
 */
class LoginServiceClient extends ServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('fr_services_login_endpoint', 'http://213.212.70.93/api/login');
    }

    parent::__construct($endpoint, 0);
  }

  /**
   * Log in user to LDAP.
   *
   * @param $username
   * @param $password
   * @return mixed|null
   */
  public function login($username, $password) {
    $username = HttpClient::urlencode_rfc3986($username);
    $password = HttpClient::urlencode_rfc3986($password);
    $parameters = array(
      'username' => $username,
      'password' => $password,
    );
    $data = $this->executeGet(NULL, $parameters);

    return $data;
  }

}
