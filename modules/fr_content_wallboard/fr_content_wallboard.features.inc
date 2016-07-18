<?php
/**
 * @file
 * fr_content_wallboard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fr_content_wallboard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function fr_content_wallboard_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function fr_content_wallboard_node_info() {
  $items = array(
    'wallboard' => array(
      'name' => t('Wallboard'),
      'base' => 'node_content',
      'description' => t('Create slides with dashboards.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
