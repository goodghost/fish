<?php

/**
 * Implements hook_views_data_alter().
 */
function fr_user_views_data_alter(&$data) {
  $data['users']['remote'] = array(
    'title' => t('Remote'),
    'real field' => 'data',
    'help' => t('Flag to mark the user as remote.'),
    'filter' => array(
      'handler' => 'fr_user_views_handler_filter_user_remote',
    ),
  );
}
