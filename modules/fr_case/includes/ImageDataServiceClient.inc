<?php

/**
 * Class ImageDataServiceClient
 */
class ImageDataServiceClient extends ServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('fr_services_image_data_endpoint', 'http://213.212.70.93/api/imagedata');
    }

    if ($cacheTtl === NULL) {
      $cacheTtl = variable_get('fr_services_image_data_cache', 0);
    }

    parent::__construct($endpoint, $cacheTtl);
  }

  /**
   * Get image details by id.
   *
   * @param $imageId
   *
   * @return mixed|null
   */
  public function getImageDataById($imageId) {
    $data = $this->executeGet($imageId);

    return $data;
  }

}
