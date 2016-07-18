<?php

/**
 * Class BlogServiceClient
 */
class BlogServiceClient extends HttpClient {
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
  public function __construct($endpoint, $cache_ttl = 0) {
    parent::__construct(NULL, new HttpClientJSONFormatter(), FALSE, new HttpClientCurlDelegate());

    $this->setEndpoint($endpoint);
    $this->setCacheTtl($cache_ttl);
  }

  /***
   * Executes a GET request.
   *
   * @param String $path
   * @param int $cache_ttl
   *   Time to keep the data in persistent cache in seconds
   * @return mixed|null
   */
  public function get($path = NULL, $cache_ttl = NULL) {
    if ($cache_ttl === NULL) {
      $cache_ttl = $this->getCacheTtl();
    }

    // Build an unique cache key
    $key = sprintf("%s/%s", $this->getEndpoint(), $path);
    $cache_key = "kis_services:" . md5($key);
    $data = NULL;

    // Check if response is cached statically. This is to avoid multiple calls to fetch the same inside single request.
    $static_cache = &drupal_static($cache_key);
    if ($static_cache) {
      $data = $static_cache;
      $data = $this->postProcess($data);
      return $data;
    }

    // If user requested persistent caching, please try to request data form persistent cache.
    if (empty($data) && $cache_ttl && $cache = cache_get($cache_key, 'cache_kis_services')) {
      $data = $cache->data;
      $data = $this->postProcess($data);
      return $data;
    }

    // If data is not in cache, please call service.
    if (empty($data)) {
      // Handle any exceptions
      try {
        $data = parent::get(implode("/", array_filter(array($this->getEndpoint(), $path))));
      }
      catch (Exception $e) {
        watchdog('kis_services', "Failed to GET %key: %error", array('%key' => $key, '%error' => $e->getMessage()), WATCHDOG_ERROR);
        // Return the expected data format to upstream functions.
        return array();
      }
    }

    // If cache is enabled for this request, please store the response.
    if ($cache_ttl) {
      watchdog('kis_services', "Set Cache for %key as %cache_key", array('%key' => $key, '%cache_key' => $cache_key), WATCHDOG_NOTICE);
      cache_set($cache_key, $data, 'cache_kis_services', REQUEST_TIME + $cache_ttl);
    }

    // Store data in static cache, so all of the above is not repeated.
    $static_cache = $data;

    // If not data returned, please log this fact
    if (empty($data)) {
      watchdog('kis_services', 'No results returned from the service %key', array('%key' => $key), WATCHDOG_WARNING);
    }

    // Postprocess response. This can't be cached.
    $data = $this->postProcess($data);
    return $data;
  }

  /**
   * Allows subclasses to transforms the data after making the call
   *
   * @param $data
   */
  protected function postProcess($data) {
    $posts = array();
    foreach ($data['posts'] as $post) {
      $thumb = NULL;
      // Thumbnail is specified
      if (isset($post['thumbnail'])) {
        $thumb = $post['thumbnail'];
      }
      // Get thumbnail from first attachment
      elseif (isset($post['attachments']) && is_array($post['attachments'])) {
        foreach($post['attachments'] as $attachment) {
          if (fnmatch('image/*', $attachment['mime_type'])) {
            $thumb = $attachment['url'];
            break;
          }
        }
      }

      // Get thumbnail from post body
      if (empty($thumb)) {
        $doc = new DOMDocument();
        $doc->loadHTML($post['content']);

        foreach ($doc->getElementsByTagName('img') as $image) {
          $thumb = $image->getAttribute('src');
          break;
        }
      }

      $posts[] = new BlogPost($post['id'], $post['title_plain'], $post['excerpt'], $post['url'], Datetime::createFromFormat('Y-m-d H:i:s', $post['date']), $post['author']['name'], $thumb);
    }
    return $posts;
  }
}
