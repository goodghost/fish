<?php
/**
 * @file
 * fr_content_wallboard.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function fr_content_wallboard_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-wallboard-field_dashboards'
  $field_instances['node-wallboard-field_dashboards'] = array(
    'bundle' => 'wallboard',
    'default_value' => array(),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(),
        'type' => 'entityreference_entity_id',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(),
        'type' => 'entityreference_entity_id',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_dashboards',
    'label' => 'Dashboards',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference_view_widget',
      'settings' => array(
        'allow_duplicates' => 0,
        'close_modal' => 1,
        'pass_argument' => 1,
        'pass_arguments' => '',
        'rendered_entity' => 0,
        'view' => 'wallboard_entiy_reference_view_widget|entityreference_view_widget_1',
        'view_mode' => 'full',
      ),
      'type' => 'entityreference_view_widget',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-wallboard-field_slide_duration'
  $field_instances['node-wallboard-field_slide_duration'] = array(
    'bundle' => 'wallboard',
    'default_value' => array(
      0 => array(
        'value' => 6,
      ),
    ),
    'deleted' => 0,
    'description' => 'Set slide duration in second for example: 1, 2, 6',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_slide_duration',
    'label' => 'Slide duration',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => 1,
      'prefix' => '',
      'suffix' => 'seconds',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-wallboard-field_slide_effect'
  $field_instances['node-wallboard-field_slide_effect'] = array(
    'bundle' => 'wallboard',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_slide_effect',
    'label' => 'Slide effect',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-wallboard-field_slide_transition_speed'
  $field_instances['node-wallboard-field_slide_transition_speed'] = array(
    'bundle' => 'wallboard',
    'default_value' => array(
      0 => array(
        'value' => 0.2,
      ),
    ),
    'deleted' => 0,
    'description' => 'Set slide transition speed in seconds for example: 0.2, 0.5, 1, 2.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_slide_transition_speed',
    'label' => 'Slide transition speed',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => 0.1,
      'prefix' => '',
      'suffix' => 'seconds',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-wallboard-og_group_ref'
  $field_instances['node-wallboard-og_group_ref'] = array(
    'bundle' => 'wallboard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'og_group_ref',
    'label' => 'Groups audience',
    'required' => FALSE,
    'settings' => array(
      'behaviors' => array(
        'og_widget' => array(
          'admin' => array(
            'widget_type' => 'entityreference_autocomplete',
          ),
          'default' => array(
            'widget_type' => 'options_select',
          ),
          'status' => TRUE,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'custom settings' => FALSE,
        'label' => 'Full',
        'type' => 'og_list_default',
      ),
      'teaser' => array(
        'custom settings' => FALSE,
        'label' => 'Teaser',
        'type' => 'og_list_default',
      ),
    ),
    'widget' => array(
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Dashboards');
  t('Groups audience');
  t('Set slide duration in second for example: 1, 2, 6');
  t('Set slide transition speed in seconds for example: 0.2, 0.5, 1, 2.');
  t('Slide duration');
  t('Slide effect');
  t('Slide transition speed');

  return $field_instances;
}
