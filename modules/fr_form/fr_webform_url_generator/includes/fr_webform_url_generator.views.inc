<?php

function fr_webform_url_generator_views_data() {
  $data = array();

  $data['fr_form_operations']['table']['group'] = t('Webform picker');
  $data['fr_form_operations']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );

  $data['fr_form_operations']['operation'] = array(
    'title' => t('Available operations'),
    'help' => t('Available operations of FISH webform'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_operations',
    ),
  );

  return $data;
}