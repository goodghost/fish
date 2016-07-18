<?php

/**
 * Class DataSetServiceClient
 */
class DataSetServiceClient extends ServiceClient {

  private $parameters = array();

  /**
   * Prepare connection.
   *
   * @param string $endpoint
   * @param int $cacheTtl
   */
  public function __construct($endpoint = NULL, $cacheTtl = NULL) {
    if (empty($endpoint)) {
      $endpoint = variable_get('fr_services_datasets_endpoint', 'http://213.212.70.93/api/views');
    }

    if ($cacheTtl === NULL) {
      $cacheTtl = variable_get('fr_services_datasets_cache', 0);
    }

    parent::__construct($endpoint, $cacheTtl);
  }

  /**
   * Gel list of datasets.
   *
   * @return mixed|null
   *   List of datasets.
   */
  public function getList() {
    return $this->executeGet();
  }

  /**
   * Set fields to be returned from dataset endpoint.
   *
   * @param array $fields
   */
  public function setFields(array $fields = array()) {
    $this->parameters['fields'] = array();
    foreach ($fields as $field_key => $field) {
      if (!empty($field['enabled'])) {
        $this->parameters['fields'][] = $field_key;
      }
    }
  }

  /**
   * Set filters used to query dataset endpoint.
   *
   * @param array $filters
   */
  public function setFilters(array $filters = array()) {
    $filters_prepared = array();
    foreach ($filters as $filter) {
      if (!isset($filter['value'])) {
        continue;
      }
      // Handle "between" operator (filter).
      elseif (is_array($filter['value']) && $filter['operator'] == 'between') {
        list($min, $max) = array_values($filter['value']);
        // Add MIN range: "Is greater than or equal to" operator.
        $filters_prepared[] = array(
          'field' => $filter['field'],
          'operator' => '>=',
          'value' => $min,
        );

        // Add MAX range: "Is less than or equal to" operator.
        $filters_prepared[] = array(
          'field' => $filter['field'],
          'operator' => '<=',
          'value' => $max,
        );
      }
      else {
        $filters_prepared[] = array(
          'field' => $filter['field'],
          'operator' => $filter['operator'],
          'value' => $filter['value'],
        );
      }
    }
    $this->parameters['filters'] = $filters_prepared;
  }

  /**
   * Get data of dataset.
   *
   * @param $id
   *   Dataset id.
   *
   * @return array
   *   Dataset data.
   */
  public function getData($id) {
    $id = HttpClient::urlencode_rfc3986($id);
    return $this->executeGet("$id/data", $this->parameters);
  }

  /**
   * Get structure of dataset.
   *
   * @param $datasetId
   *   Dataset id.
   *
   * @return array
   *   Dataset structure.
   */
  public function getStructure($datasetId) {
    $datasetId = HttpClient::urlencode_rfc3986($datasetId);
    return $this->executeGet($datasetId);
  }

  /**
   * Get structure of dataset as assoc array.
   *
   * @param $datasetId
   *   Dataset id.
   *
   * @return array
   *   Dataset structure.
   */
  public function getStructureAssoc($datasetId) {
    $structureAssoc = array();
    if ($structure = $this->getStructure($datasetId)) {
      foreach ($structure['fields'] as $fieldDefinition) {
        $structureAssoc[$fieldDefinition['name']] = $fieldDefinition;
      }
    }
    return $structureAssoc;
  }

  /**
   * Get case ID by reference number.
   *
   * @param $refNumber
   * @return null
   */
  public function getCaseIdByRefNumber($refNumber) {
    $this->parameters['fields'] = array('case_id');
    $this->parameters['filters'] = array(array(
      'field' => 'reference',
      'operator' => '=',
      'value' => check_plain($refNumber),
    ));

    $data = $this->executeGet('fish_workflow.case_quick_ref/data', $this->parameters);

    if (!empty($data['result'][0]['case_id'])) {
      return $data['result'][0]['case_id'];
    }
    else {
      return NULL;
    }
  }

  /**
   * Set limit of returned entries from dataset endpoint.
   *
   * @param int $limit
   */
  public function setLimit($limit = 0) {
    $this->parameters['limit'] = $limit;
  }

  /**
   * Set offset of returned entries from dataset endpoint.
   *
   * @param int $offset
   */
  public function setOffset($offset = 0) {
    $this->parameters['offset'] = $offset;
  }

  /**
   * Set sorting for dataset query.
   *
   * @param int $fieldToSortBy
   */
  public function setSorting($fieldToSortBy) {
    $this->parameters['sort'] = $fieldToSortBy;
  }

  /**
   * Set order for dataset query.
   *
   * @param int $sortingOrder
   */
  public function setOrder($sortingOrder) {
    $this->parameters['order'] = $sortingOrder;
  }

  /**
   * Helper method to export dataset structure and data.
   *
   * @param $view_id
   * @param array $fields
   * @param array $filters
   * @param int $limit
   *
   * @return array
   *   Exported array.
   */
  public static function export($view_id, array $fields = array(), array $filters = array(), $limit = 0, $offset = 0, $sorting = NULL, $order = NULL) {
    $client = new self;

    // Set query parameters.
    $client->setFields($fields);
    $client->setFilters($filters);

    if ($limit) {
      $client->setLimit($limit);
    }
    if ($offset) {
      $client->setOffset($offset);
    }
    if ($sorting) {
      $client->setSorting($sorting);
    }
    if ($order) {
      $client->setOrder($order);
    }

    // Get data.
    $data = $client->getData($view_id);

    // Get structure.
    $structure = $client->getStructure($view_id);

    // Combine data with structure.
    $export = array();
    foreach ($data['result'] as $i => $row) {
      foreach ($row as $field_name => $field_value) {
        foreach ($structure['fields'] as $field_structure) {
          if ($field_structure['name'] == $field_name && (!empty($fields[$field_name])) || in_array($field_name, $fields)) {
            if (!isset($export[$i])) {
              $export[$i] = array();
            }
            $export[$i][] = array(
              'name' => $field_name,
              'type' => $field_structure['type'],
              'value' => $field_value,
            );
            break;
          }
        }
      }
    }

    return $export;
  }

}
