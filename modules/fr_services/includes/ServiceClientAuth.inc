<?php

/**
 * Class ServiceClientAuth
 */
class ServiceClientAuth implements HttpClientAuthentication {
  /**
   * Used by the HttpClient to authenticate requests.
   *
   * @param HttpClientRequest $request
   * @return void
   */
  public function authenticate($request) {
    global $user;
    if (isset($user->data['remote_session_id'])) {
      $request->setHeader('session_id', $user->data['remote_session_id']);
    }
  
    if (isset($user->data['service_user']['fd_id'])) {
      $request->setHeader('user_id', $user->data['service_user']['fd_id']);
    }
  }
}