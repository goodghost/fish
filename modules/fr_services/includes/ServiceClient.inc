<?php

/**
 * Class ServiceClient
 */
abstract class ServiceClient extends HttpClient {
  /**
   * Configurable Ttl for cache. Set to 0 to disable cache.
   */
  private $cacheTtl;

  /**
   * Endpoint for this service
   */
  private $endpoint;

  /**
   * @return mixed
   */
  public function getEndpoint() {
    return $this->endpoint;
  }

  /**
   * @param mixed $endpoint
   */
  public function setEndpoint($endpoint) {
    $this->endpoint = $endpoint;
  }

  /**
   * @return mixed
   */
  public function getCacheTtl() {
    return $this->cacheTtl;
  }

  /**
   * @param mixed $cacheTtl
   */
  public function setCacheTtl($cacheTtl) {
    $this->cacheTtl = $cacheTtl;
  }

  /**
   * Creates a client with JSON as formatter.
   *
   * @param HttpClientAuthentication|null $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint, $cacheTtl = 0) {
    parent::__construct(NULL, new HttpClientJSONFormatter(), FALSE, new HttpClientCurlDelegate());

    // Set the client to accept GZiped responses.
    $this->options['curlopts'][CURLOPT_ENCODING] = 'gzip';

    $this->setEndpoint($endpoint);
    $this->setCacheTtl($cacheTtl);
    $this->setAuthentication(new ServiceClientAuth());
  }

  /**
   * Executes a GET request.
   *
   * @param string $path
   *   Path of GET request.
   * @param array $parameters
   *   Query parameters that will be added to URL.
   * @param int $cacheTtl
   *   Time to keep the data in persistent cache in seconds.
   * @param bool $reset
   *   Set to TRUE to get fresh (not cached) data from the service.
   *
   * @return mixed|null
   */
  public function executeGet($path = NULL, $parameters = array(), $cacheTtl = NULL, $reset = FALSE) {
    if ($cacheTtl === NULL) {
      $cacheTtl = $this->getCacheTtl();
    }

    // Build an unique cache key
    $key = sprintf('%s/%s?%s', $this->getEndpoint(), $path, http_build_query($parameters));
    $cacheKey = 'fr_services:' . md5($key);
    $data = NULL;
    // Check is response is cached statically. This is to avoid multiple calls to fetch the same inside single request.
    $staticCache = &drupal_static($cacheKey);
    if (!$reset && $staticCache) {
      $data = $staticCache;
      $data = $this->postProcess($data);
      return $data;
    }

    // If user requested persistent caching, please try to request data form persistent cache.
    if (!$reset && empty($data) && $cacheTtl && $cache = cache_get($cacheKey, 'cache_fr_services')) {
      $data = $cache->data;
      $data = $this->postProcess($data);
      return $data;
    }

    // If data is not in cache, please call service.
    if ($reset || empty($data)) {
      // Handle any exceptions.
      try {
        $data = $this->execute(new ServiceClientRequest(implode('/', array_filter(array($this->getEndpoint(), $path))), array(
          'method' => 'GET',
          'parameters' => $parameters,
        )));
      }
      catch (Exception $e) {
        watchdog('fr_services', 'Failed to GET %key: %error', array('%key' => $key, '%error' => $e->getMessage()), WATCHDOG_ERROR);

        // Return the expected data format to upstream functions.
        return array();
      }
    }

    // If no data returned, please log this fact.
    if (empty($data)) {
      watchdog('fr_services', 'No results returned from the service %key', array('%key' => $key), WATCHDOG_WARNING);
    }

    // Store data in static cache, so all of the above is not repeated.
    $staticCache = $data;

    // If cache is enabled for this request, please store the response.
    if ($cacheTtl) {
      watchdog('fr_services', 'Set Cache for %key as %cache_key', array('%key' => $key, '%cache_key' => $cacheKey), WATCHDOG_NOTICE);
      cache_set($cacheKey, $data, 'cache_fr_services', REQUEST_TIME + $cacheTtl);
    }

    // Postprocess response. This can't be cached.
    $data = $this->postProcess($data);
    return $data;
  }

  /**
   * Executes a POST request.
   *
   * @param $data
   *
   * @param array $parameters
   *
   * @return mixed|null
   * @throws ServiceException
   */
  public function executePost($data, $parameters = array()) {
    // No cache of POST requests.
    try {
      return parent::post($this->getEndpoint(), $data, $parameters);
    }
    catch (Exception $e) {
      $message = sprintf('Failed to POST %s?%s: %s', $this->getEndpoint(), http_build_query($parameters), $e->getMessage());
      watchdog('fr_services', $message, array(), WATCHDOG_ERROR);
      throw new ServiceException($message);
    }
  }

  /**
   * Executes a PUT request.
   *
   * @param $data
   * @param array $parameters
   * @return mixed|null
   * @throws ServiceException
   */
  public function executePut($data, $parameters = array()) {
    // No cache of PUT requests.
    try {
      return parent::put($this->getEndpoint(), $data, $parameters);
    }
    catch (Exception $e) {
      $message = sprintf('Failed to PUT %s?%s: %s', $this->getEndpoint(), http_build_query($parameters), $e->getMessage());
      watchdog('fr_services', $message, array(), WATCHDOG_ERROR);
      throw new ServiceException($message);
    }
  }

  /**
   * Executes a DELETE request.
   *
   * @param array $parameters
   * @return mixed|null
   * @throws ServiceException
   */
  public function executeDelete($parameters = array()) {
    // No cache of DELETE requests.
    try {
      return parent::delete($this->getEndpoint(), $parameters);
    }
    catch (Exception $e) {
      $message = sprintf('Failed to DELETE %s?%s: %s', $this->getEndpoint(), http_build_query($parameters), $e->getMessage());
      watchdog('fr_services', $message, array(), WATCHDOG_ERROR);
      throw new ServiceException($message);
    }
  }

  /**
   * Allows subclasses to transforms the data after making the call.
   *
   * @param array $data
   *   Data from the response.
   *
   * @return array
   *   Modified data.
   */
  protected function postProcess($data) {
    return $data;
  }

  /**
   * Returns response headers
   *
   * @return array
   *   Response headers.
   */
  public function getResponseHeaders() {
    if ($response = $this->lastResponse) {
      $retVal = array();
      $fields = explode("\r\n", preg_replace('/\x0D\x0A[\x09\x20]+/', ' ', $response->headers));
      foreach ($fields as $field) {
        if (preg_match('/([^:]+): (.+)/m', $field, $match)) {
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

}
