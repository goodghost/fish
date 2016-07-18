<?php

/**
 * Class ServiceClient
 */
abstract class ServiceClient extends HttpClient {
  /**
   * @var
   *
   * Configurable Ttl for cache. Set to 0 to disable cache.
   */
  private $cacheTtl;

  /**
   * @var
   *
   * Endpoint for this service
   */
  private $endpoint;

  /**
   * @param mixed $endpoint
   */
  public function setEndpoint($endpoint)
  {
    $this->endpoint = $endpoint;
  }

  /**
   * @return mixed
   */
  public function getEndpoint()
  {
    return $this->endpoint;
  }

  /**
   * @param mixed $cacheTtl
   */
  public function setCacheTtl($cacheTtl)
  {
    $this->cacheTtl = $cacheTtl;
  }

  /**
   * @return mixed
   */
  public function getCacheTtl()
  {
    return $this->cacheTtl;
  }

  /**
   * Creates a client with JSON as formatter.
   *
   * @param HttpClientAuthentication|null $endpoint
   * @param int $cache_ttl
   */
  public function __construct($endpoint, $cache_ttl = 0, $access_key = NULL, $access_token = NULL) {
    parent::__construct(NULL, new HttpClientJSONFormatter(), FALSE, new HttpClientCurlDelegate());

    // Set the client to accept GZiped responses.
    $this->options['curlopts'][CURLOPT_ENCODING] = "gzip";

    $this->setEndpoint($endpoint);
    $this->setCacheTtl($cache_ttl);
    $this->setAuthentication(new KisServiceClientAuth(
      $access_key ? $access_key :variable_get("kis_service_access_key", "access_token"),
      $access_token ? $access_token :variable_get("kis_service_access_token", "kicbus")));
  }

  /***
   * Executes a GET request.
   *
   * @param String $path
   * @param array $parameters
   * @param int $cache_ttl
   *   Time to keep the data in persistent cache in seconds
   * @return mixed|null
   */
  public function get($path = NULL, $parameters = array(), $cache_ttl = NULL, $reset = FALSE) {
    if ($cache_ttl === NULL) {
      $cache_ttl = $this->getCacheTtl();
    }

    // Build an unique cache key
    $key = sprintf("%s/%s?%s", $this->getEndpoint(), $path, http_build_query($parameters));
    $cache_key = "kis_services:" . md5($key);
    $data = NULL;

    // Check is response is cached statically. This is to avoid multiple calls to fetch the same inside single request.
    $static_cache = &drupal_static($cache_key);
    if (!$reset && $static_cache) {
      $data = $static_cache;
      $data = $this->postProcess($data);
      return $data;
    }

    // If user requested persistent caching, please try to request data form persistent cache.
    if (!$reset && empty($data) && $cache_ttl && $cache = cache_get($cache_key, 'cache_kis_services')) {
      $data = $cache->data;
      $data = $this->postProcess($data);
      return $data;
    }

    // If data is not in cache, please call service.
    if ($reset || empty($data)) {
      // Handle any exceptions
      try {
        $data = parent::get(implode("/", array_filter(array($this->getEndpoint(), rawurlencode($path)))), $parameters);
      }
      catch (Exception $e) {
        watchdog('kis_services', "Failed to GET %key: %error", array('%key' => $key, '%error' => $e->getMessage()), WATCHDOG_ERROR);
        // Return the expected data format to upstream functions.
        return array();
      }
    }

    // If not data returned, please log this fact
    if (empty($data)) {
      watchdog('kis_services', 'No results returned from the service %key', array('%key' => $key), WATCHDOG_WARNING);
    }

    // Store data in static cache, so all of the above is not repeated.
    $static_cache = $data;

    // If cache is enabled for this request, please store the response.
    if ($cache_ttl) {
      watchdog('kis_services', "Set Cache for %key as %cache_key", array('%key' => $key, '%cache_key' => $cache_key), WATCHDOG_NOTICE);
      cache_set($cache_key, $data, 'cache_kis_services', REQUEST_TIME + $cache_ttl);
    }

    // Postprocess response. This can't be cached.
    $data = $this->postProcess($data);
    return $data;
  }

  /**
   * Executes a POST request.
   *
   * @param $data
   * @param array $parameters
   * @return mixed|null
   */
  public function post($data, $parameters = array()) {
    // No cache of POST requests.
    try {
      return parent::post($this->getEndpoint(), $data, $parameters);
    }
    catch (Exception $e) {
      $message = sprintf("Failed to POST %s?%s: %s", $this->getEndpoint(), http_build_query($parameters), $e->getMessage());
      watchdog('kis_services', $message, array(), WATCHDOG_ERROR);
      throw new KisServicesException($message);
    }
  }

  /**
   * Executes a PUT request.
   *
   * @param $data
   * @param array $parameters
   * @return mixed|null
   */
  public function put($data, $parameters = array()) {
    // No cache of PUT requests.
    try {
      return parent::put($this->getEndpoint(), $data, $parameters);
    }
    catch (Exception $e) {
      $message = sprintf("Failed to PUT %s?%s: %s", $this->getEndpoint(), http_build_query($parameters), $e->getMessage());
      watchdog('kis_services', $message, array(), WATCHDOG_ERROR);
      throw new KisServicesException($message);
    }
  }

  /**
   * Executes a DELETE request.
   *
   * @param array $parameters
   * @return mixed|null
   */
  public function delete($parameters = array()) {
    // No cache of DELETE requests.
    try {
      return parent::delete($this->getEndpoint(), $parameters);
    }
    catch (Exception $e) {
      $message = sprintf("Failed to DELETE %s?%s: %s", $this->getEndpoint(), http_build_query($parameters), $e->getMessage());
      watchdog('kis_services', $message, array(), WATCHDOG_ERROR);
      throw new KisServicesException($message);
    }
  }

  /**
   * Allows subclasses to transforms the data after making the call
   *
   * @param $data
   */
  protected function postProcess($data) {
    return $data;
  }

  /**
   * Returns reponse headers
   *
   * @param $header
   * @return array
   */
  public function get_reponse_headers() {
    if ($response = $this->lastResponse) {
      $retVal = array();
      $fields = explode("\r\n", preg_replace('/\x0D\x0A[\x09\x20]+/', ' ', $response->headers));
      foreach( $fields as $field ) {
        if( preg_match('/([^:]+): (.+)/m', $field, $match) ) {
          $match[1] = preg_replace('/(?<=^|[\x09\x20\x2D])./e', 'strtoupper("\0")', strtolower(trim($match[1])));
          if( isset($retVal[$match[1]]) ) {
            $retVal[$match[1]] = array($retVal[$match[1]], $match[2]);
          } else {
            $retVal[$match[1]] = trim($match[2]);
          }
        }
      }
      return $retVal;
    }

    return NULL;
  }

  /**
   * Sanitises language code so it's always in format xx-XX
   *
   * @param $code
   */
  public static function sanitizeCultureCode($code) {
    // English language will be british.
    if ($code == 'en') {
      return 'en-GB';
    }

    // Already matching the pattern. Not using regex here as it has it's performance hit.
    if (strlen($code) == 5 && !is_numeric($code) && substr($code, 2, 1) == '-') {
      return $code;
    }

    // Already matching the pattern
    if (strlen($code) == 2 && !is_numeric($code)) {
      return implode('-', array($code, strtoupper($code)));
    }

    // Not matching any patterns
    return NULL;
  }

}
