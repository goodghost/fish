<?php

/**
 * Class KisServiceClientAuth
 */

class KisServiceClientAuth implements HttpClientAuthentication {
  private $tokenKey;
  private $tokenValue;

  /**
   * KisServiceClientAuth constructor
   *
   * @param $token_key
   * @param $token_value
   */
  public function __construct($token_key, $token_value) {
    $this->tokenKey = $token_key;
    $this->tokenValue = $token_value;
  }

  /**
   * Used by the HttpClient to authenticate requests.
   *
   * @param HttpClientRequest $request
   * @return void
   */
  public function authenticate($request) {
    $request->parameters[$this->tokenKey] = $this->tokenValue;
    //$request->setHeader($this->tokenKey, $this->tokenValue);
  }
}
