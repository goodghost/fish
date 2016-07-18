<?php

/**
 * Class ServiceException
 */
class ServiceException extends HttpClientException {

  /**
   * Factory method to create ServiceException from existing exception object.
   * @param HttpClientException $e
   * @return ServiceException
   */
  public static function createFromException(HttpClientException $e) {
    return new self($e->getMessage(), $e->getCode(), $e->getResponse(), $e);
  }
}
