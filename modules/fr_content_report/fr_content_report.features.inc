<?php
/**
 * @file
 * fr_content_report.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fr_content_report_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function fr_content_report_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function fr_content_report_node_info() {
  $items = array(
    'report' => array(
      'name' => t('Report'),
      'base' => 'node_content',
      'description' => t('Use this content type to create new report.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
