<?php
/**
 * @file
 * fr_content_dashboard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fr_content_dashboard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function fr_content_dashboard_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function fr_content_dashboard_node_info() {
  $items = array(
    'dashboard' => array(
      'name' => t('Dashboard'),
      'base' => 'node_content',
      'description' => t('Create dashboard pages similar to iGoogle.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
