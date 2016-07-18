<?php

/**
 * This is a convenience class that allows the manipulation of a http request
 * before it's handed over to curl.
 */
class ServiceClientRequest extends HttpClientRequest {

  /**
   * Returns the url taken the parameters into account.
   */
  public function url() {
    if (empty($this->parameters)) {
      return $this->url;
    }

    return $this->url . '?' . http_build_query($this->parameters);
  }

}
