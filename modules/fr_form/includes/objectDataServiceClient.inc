<?php

/**
 * Class ImageDataServiceClient
 */
class ObjectDataServiceClient extends DataSetServiceClient {

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('fr_services_object_data_endpoint', 'http://213.212.70.93/api');
    }

    if ($cacheTtl === NULL) {
      $cacheTtl = variable_get('fr_services_object_data_cache', 0);
    }

    parent::__construct($endpoint, $cacheTtl);
  }

  /**
   * Get categories.
   */
  public function getCategories() {
    return $this->executeGet("categories");
  }

  /**
   * Get SRQ List
   */
  public function getSRQList() {
    return $this->executeGet("srq/list");
  }

  /**
   * Get objects by category.
   */
  public function getObjectsByCategory($category = NULL) {
    if (isset($category)) {
      return $this->executeGet("categories/views/$category");
    } else {
      return $this->executeGet("categories/views");
    }
  }

  /**
   * Get fields structure for provided category
   */
  public function getCategoryStructure($category) {
    $data = $this->executeGet("categories/$category");
    return $data['categories'][$category];
  }

  /**
   * Get fields structure for provided object
   */
  public function getObjectStructure($object) {
    $data = $this->executeGet("views/$object");
    return $data;
  }

  /**
   * Get item.
   *
   * @return mixed|null
   *   Item.
   */
  public function getItem($object_id, $item_id) {
    $object_id = HttpClient::urlencode_rfc3986($object_id);
    $item_id = HttpClient::urlencode_rfc3986($item_id);
    return $this->executeGet("views/$object_id/data/$item_id");
  }

  /**
   * Insert item.
   *
   * @return mixed|null
   *   Item.
   */
  public function insertItem($object_id, $data) {
    $endpoint = variable_get('fr_services_object_data_endpoint', 'http://213.212.70.93/api/views');
    $endpoint = $endpoint."/$object_id/add";
    $this->setEndpoint($endpoint);
    return $this->executePost($data);
  }

  /**
   * Send SRQ request.
   *
   * @return mixed|null
   *   Item.
   */
  public function insertSRQItem($srq_data) {
    $endpoint = variable_get('fr_services_srq_data_endpoint', 'http://213.212.70.93/api/srq/add');
    $this->setEndpoint($endpoint);
    return $this->executePost($srq_data);
  }

  /**
   * Update item.
   *
   * @return mixed|null
   *   Item.
   */
  public function updateItem($object_id, $data) {
    $endpoint = variable_get('fr_services_object_data_endpoint', 'http://213.212.70.93/api/views');
    $endpoint = $endpoint."/$object_id/update";
    $this->setEndpoint($endpoint);
    return $this->executePost($data);
  }
}
