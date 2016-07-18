<?php
/**
 * @file
 * fr_content_report.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function fr_content_report_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_dataset'
  $field_bases['field_dataset'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_dataset',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fr_dataset_field',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'dataset',
  );

  return $field_bases;
}
