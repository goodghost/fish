<?php
/**
 * @file
 * fr_content_dashboard_block.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fr_content_dashboard_block_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function fr_content_dashboard_block_node_info() {
  $items = array(
    'dashboard_block' => array(
      'name' => t('Dashboard block'),
      'base' => 'node_content',
      'description' => t('Add content and/or links to the dashboard. '),
      'has_title' => '1',
      'title_label' => t('Content title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
