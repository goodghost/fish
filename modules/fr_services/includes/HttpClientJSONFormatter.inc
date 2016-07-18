<?php

/**
 * Class for handling json responses.
 * Returns a SimpleXML object
 *
 * @author Simon Ljungberg <simon.ljungberg@goodold.se>
 */

class HttpClientJSONFormatter implements HttpClientFormatter {
  /**
   * Creates a HttpClientJSONFormatter.
   */
  public function __construct() {}

  /**
   * Serializes arbitrary data to the implemented format.
   * Directly stolen from http_server by Hugo Wetterberg
   *
   * @param mixed $data
   *  The data that should be serialized.
   * @return string
   *  The serialized data as a string.
   */
  public function serialize($data) {
    return drupal_json_encode($data);
  }

  /**
   * Return the mime type that the formatter can parse.
   */
  public function accepts(){
    return $this->mimeType();
  }

  /**
   * Return the content type form the data the formatter generates.
   */
  public function contentType(){
    return $this->mimeType();
  }

  /**
   * Unserializes data in the implemented format.
   *
   * @param string $data
   *  The data that should be unserialized.
   * @return mixed
   *  The unserialized data.
   */
  public function unserialize($data) {
    return drupal_json_decode($data);
  }

  /**
   * Return MIME Type this formatter supports
   * @return string
   */
  public function mimeType() {
    return 'application/json';
  }
}
