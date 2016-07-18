<?php
/**
 * @file
 * Helper functions for Google Charts table.
 */

/**
 * Form callback for Google Charts table settings.
 */
function fr_dataset_field_display_table_settings_form(&$form, &$form_state, $submitted_values, $display_settings, $item, $delta) {
  if (isset($submitted_values['fields'])) {
    $fields = fr_dataset_field_parse_fields($submitted_values['fields']);
  }
  elseif (isset($item['fields'])) {
    $fields = unserialize($item['fields']);
  }
  else {
    $fields = array();
  }

  $element = array();

  // Records per page.
  $element['page_size'] = array(
    '#title' => t('Records per page'),
    '#description' => t('Define how many rows to display in one page (pagination).'),
    '#type' => 'select',
    '#options' => array(
        0 => t('Unlimited (display all)'),
      ) + range(0, 10) + array_combine(range(20, 40, 10), range(20, 40, 10)) + array_combine(range(50, 200, 50), range(50, 200, 50)),
    '#default_value' => isset($display_settings['page_size']) ? $display_settings['page_size'] : 20,
  );

  // Prepare tokens for description.
  $tokens = '';
  foreach ($fields as $field_key => $field) {
    if ($field['enabled']) {
      $tokens .= '<strong>{' . $field_key . '}</strong>';
      if ($field !== end($fields)) {
        $tokens .= ', ';
      }
    }
  }

  // Examples for URL tokens usage.
  $examples = array(
    'internal-url/<strong>{example_id}</strong>',
    'http://google.com/#q=<strong>{my_field}</strong>',
  );
  $tokens = t('Available field replacements: !tokens.', array('!tokens' => $tokens));
  $examples = t('Examples: !examples', array('!examples' => theme('item_list', array('items' => $examples))));
  $help_text = "$tokens<br/>$examples";

  $element['overrides'] = array(
    '#title' => t('Override field output'),
    '#type' => 'item',
  );

  // Assign POSTed values.
  if (isset($form_state['input']['field_dataset'][LANGUAGE_NONE][$delta]['display_settings']['overrides'])) {
    $overrides = $form_state['input']['field_dataset'][LANGUAGE_NONE][$delta]['display_settings']['overrides'];
  }
  // Assign existing values.
  elseif (!isset($overrides)) {
    $overrides = $display_settings['overrides'];
  }

  // React on AJAX events.
  if (isset($form_state['triggering_element'])) {
    $triggered_element = $form_state['triggering_element'];

    // Adding new icon mapping.
    if (isset($triggered_element['#submit'][0]) && $triggered_element['#submit'][0] == 'fr_dataset_field_table_overrides_add_submit_callback') {

      $overrides[$triggered_element['#field_key']]['icons']['mapping'][] = array(
        'value' => NULL,
        'icon' => NULL,
        'icon_color' => NULL,
        'icon_placement' => 'replace',
      );
    }

    // Removing icon mapping.
    if (isset($triggered_element['#submit'][0]) && $triggered_element['#submit'][0] == 'fr_dataset_field_table_overrides_remove_submit_callback') {
      unset($overrides[$triggered_element['#field_key']]['icons']['mapping'][$triggered_element['#row_id']]);
    }
  }

  foreach ($fields as $field_key => $field) {
    $field_type = $form_state['dataset_field_types'][$field_key];

    if ($field['enabled']) {
      $element['overrides'][$field_key] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('dataset-overrides'),
        ),
      );

      $element['overrides'][$field_key]['enabled'] = array(
        '#title' => $field_key,
        '#type' => 'checkbox',
        '#default_value' => isset($display_settings['overrides'][$field_key]['enabled']) ? $display_settings['overrides'][$field_key]['enabled'] : NULL,
      );

      $element['overrides'][$field_key]['type'] = array(
          '#title' => t('Type'),
          '#type' => 'select',
          '#empty_option' => t('- Select -'),
          '#options' => array(
            'link' => t('Link'),
            'icon' => t('Icon'),
          ),
          '#default_value' => isset($display_settings['overrides'][$field_key]['type']) ? $display_settings['overrides'][$field_key]['type'] : NULL,
          '#states' => array(
            'visible' => array(
              "input[name=\"field_dataset[und][$delta][display_settings][overrides][$field_key][enabled]\"" => array('checked' => TRUE),
            ),
          ),
      );
      $element['overrides'][$field_key]['url'] = array(
        '#title' => t('Link URL'),
        '#description' => $help_text,
        '#type' => 'textfield',
        '#default_value' => isset($display_settings['overrides'][$field_key]['url']) ? $display_settings['overrides'][$field_key]['url'] : NULL,
        '#states' => array(
          'visible' => array(
            "input[name=\"field_dataset[und][$delta][display_settings][overrides][$field_key][enabled]\"" => array('checked' => TRUE),
            "select[name=\"field_dataset[und][$delta][display_settings][overrides][$field_key][type]\"" => array('value' => 'link'),
          ),
        ),
      );

      if (isset($overrides[$field_key]['icons']['mapping'])) {
        $icons_mapping = $overrides[$field_key]['icons']['mapping'];
      }
      else {
        $icons_mapping = array(
          array(
            'value' => NULL,
            'icon' => NULL,
            'icon_color' => NULL,
            'icon_placement' => 'replace',
          ),
        );
      }

      $element['overrides'][$field_key]['icons'] = array(
        '#type' => 'item',
        '#title' => t('Icons'),
        '#states' => array(
          'visible' => array(
            "input[name=\"field_dataset[und][$delta][display_settings][overrides][$field_key][enabled]\"" => array('checked' => TRUE),
            "select[name=\"field_dataset[und][$delta][display_settings][overrides][$field_key][type]\"" => array('value' => 'icon'),
          ),
        ),
      );

      $icons_info = fr_dataset_field_get_icons();
      $icon_options = array();
      foreach ($icons_info as $icon_code => $icon_info) {
        $icon_options[$icon_code] = '<span class="' . implode(' ', $icon_info['classes']) . '" title="' . $icon_code . '"></span>';
      }

      $wrapper_id = drupal_html_class($field_key);
      $icon_mapping_wrapper_id = "overrides-$wrapper_id-icon-mapping";

      // Show table only if there are added any icon mappings.
      if ($icons_mapping) {
        $element['overrides'][$field_key]['icons']['mapping'] = array(
          '#type' => 'item',
          '#prefix' => '<div class="overrides-icons-mapping-wrapper" id="' . $icon_mapping_wrapper_id . '">',
          '#suffix' => '</div>',
          '#theme' => 'dataset_table_icons_mapping',
        );
      }
      else {
        $element['overrides'][$field_key]['icons']['mapping'] = array(
          '#type' => '#value',
          '#prefix' => '<div class="overrides-icons-mapping-wrapper" id="' . $icon_mapping_wrapper_id . '">',
          '#suffix' => '</div>',
        );
      }

      $default_icon_exist = FALSE;
      foreach ($icons_mapping as $mapping) {
        if ($mapping['operator'] == 'default') {
          $default_icon_exist = TRUE;
          break;
        }
      }

      foreach ($icons_mapping as $i => $icon_mapping) {
        $element['overrides'][$field_key]['icons']['mapping'][$i] = array(
          '#type' => 'container',
        );

        $operator_options = fr_dataset_field_get_filter_operator_options($field_type);

        // It can be only one default icon.
        if ((!$default_icon_exist) || isset($icon_mapping['operator']) && $icon_mapping['operator'] == 'default') {
          $operator_options['default'] = t('Use this icon as default');
        }

        // Operator.

        $element['overrides'][$field_key]['icons']['mapping'][$i]['operator'] = array(
          '#row_id' => $i,
          '#type' => 'select',
          '#title' => t('Operator'),
          '#title_display' => 'invisible',
          '#required' => FALSE,
          '#options' => $operator_options,
          '#empty_option' => t('- Select -'),
          '#default_value' => !empty($icon_mapping['operator']) ? $icon_mapping['operator'] : NULL,
          '#ajax' => array(
            'callback' => 'fr_dataset_field_table_overrides_ajax_callback',
            'wrapper' => $icon_mapping_wrapper_id,
            'progress' => array('type' => 'none'),
          ),
        );

        // Value.

        $value_element = array();

        if (!empty($icon_mapping['operator'])) {
          $data_types = fr_dataset_field_get_data_types();

          if (isset($data_types[$field_type]['operators'][$icon_mapping['operator']])) {
            $operator_definition = $data_types[$field_type]['operators'][$icon_mapping['operator']];
          }
          else {
            $operator_definition = array();
          }

          $value_element = array(
            '#row_id' => $i,
          );

          // Operator don't use value field.
          if (isset($operator_definition['element_callback']) && $operator_definition['element_callback'] == DATASET_FIELD_FILTER_OPERATOR_NO_VALUE) {
            $value_element += array(
              '#markup' => t('N/A'),
            );
          }
          // Operator use value field so let's call function to retrieve it.
          elseif (isset($operator_definition['element_callback']) && is_callable($operator_definition['element_callback'])) {
            $value_element += call_user_func($operator_definition['element_callback'], $icon_mapping['value']);
          }
        }

        $element['overrides'][$field_key]['icons']['mapping'][$i]['value'] = $value_element;

        // Icon.

        $element['overrides'][$field_key]['icons']['mapping'][$i]['icon'] = array(
          '#row_id' => $i,
          '#type' => 'radios',
          '#options' => $icon_options,
          '#title' => t('Icon'),
          '#title_display' => 'invisible',
          '#default_value' => $icon_mapping['icon'],
        );

        // Icon color.

        $element['overrides'][$field_key]['icons']['mapping'][$i]['icon_color'] = array(
          '#row_id' => $i,
          '#type' => 'colorpicker',
          '#title' => t('Icon color'),
          '#title_display' => 'invisible',
          '#default_value' => $icon_mapping['icon_color'],
        );

        // Icon placement.

        $element['overrides'][$field_key]['icons']['mapping'][$i]['icon_placement'] = array(
          '#row_id' => $i,
          '#type' => 'radios',
          '#options' => array(
            'replace' => t('Replace value with icon'),
            'before' => t('Before value'),
            'after' => t('After value'),
          ),
          '#title' => t('Placement of icon'),
          '#title_display' => 'invisible',
          '#default_value' => $icon_mapping['icon_placement']
        );

        // Remove.

        $element['overrides'][$field_key]['icons']['mapping'][$i]['remove'] = array(
          '#row_id' => $i,
          '#field_key' => $field_key,
          '#type' => 'submit',
          // Each value needs to be unique, later (in pre_render) we change it back to "Remove".
          '#title' => t('Remove'),
          '#value' => $icon_mapping_wrapper_id . $i,
          '#submit' => array('fr_dataset_field_table_overrides_remove_submit_callback'),
          '#pre_render' => array('fr_dataset_field_submit_button_pre_render'),
          '#limit_validation_errors' => array(),
          '#attributes' => array('row_id' => $i),
          '#ajax' => array(
            'callback' => 'fr_dataset_field_table_overrides_ajax_callback',
            'wrapper' => $icon_mapping_wrapper_id,
            'progress' => array('type' => 'none'),
          ),
        );
      }

      $element['overrides'][$field_key]['icons']['add_mapping'] = array(
        '#field_key' => $field_key,
        '#title' => t('Add icon mapping'),
        '#type' => 'submit',
        '#value' => $icon_mapping_wrapper_id,
        '#submit' => array('fr_dataset_field_table_overrides_add_submit_callback'),
        '#pre_render' => array('fr_dataset_field_submit_button_pre_render'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'fr_dataset_field_table_overrides_ajax_callback',
          'wrapper' => $icon_mapping_wrapper_id,
        ),
      );

      $element['available_operations'] = array(
        '#title' => t('Available operations'),
        '#type' => 'checkboxes',
        '#options' => array(
          'view' => t('View'),
          'edit' => t('Edit'),
        ),
        '#default_value' => (isset($display_settings['available_operations'])) ? $display_settings['available_operations'] : NULL,
      );

      $element['view_operation'] = array(
        '#type' => 'textfield',
        '#description' => $help_text,
        '#title' => t('Provide a valid URL for page view'),
        '#attributes' => array('class' => array('form-type-url-generator')),
        '#default_value' => (isset($display_settings['view_operation'])) ? $display_settings['view_operation'] : '',
        '#states' => array(
          'visible' => array(
            "input[name=\"field_dataset[und][$delta][display_settings][available_operations][view]\"" => array('checked' => TRUE),
          ),
        ),
      );

      $element['edit_operation'] = array(
        '#type' => 'textfield',
        '#description' => $help_text,
        '#title' => t('Provide a valid URL for edit page'),
        '#attributes' => array('class' => array('form-type-url-generator')),
        '#default_value' => (isset($display_settings['view_operation'])) ? $display_settings['edit_operation'] : '',
        '#states' => array(
          'visible' => array(
            "input[name=\"field_dataset[und][$delta][display_settings][available_operations][edit]\"" => array('checked' => TRUE),
          ),
        ),
      );
    }
  }

  if (element_children($element['overrides'])) {

  }
  else {
    $element['overrides']['#description'] = t('Please select at least one field to display.');
  }

  return $element;
}

/**
 * Submit handler for the "Add icon mapping" button.
 * Increments the filters counter and causes a form rebuild.
 */
function fr_dataset_field_table_overrides_add_submit_callback($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "Remove" (icon mapping) button.
 * Decrements the filters counter and causes a form rebuild.
 */
function fr_dataset_field_table_overrides_remove_submit_callback($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for overrides.
 */
function fr_dataset_field_table_overrides_ajax_callback($form, &$form_state) {
  // Example parents:
  //  [0] => DRUPAL_FIELD_NAME
  //  [1] => und
  //  [2] => 0
  //  [3] => display_settings
  //  [4] => overrides
  //  [5] => DATASET_COLUMN_NAME
  //  [6] => icons
  //  [7] => mapping
  $parents = $form_state['triggering_element']['#parents'];
//  dd($form[$parents[0]][$parents[1]][$parents[2]][$parents[3]][$parents[4]][$parents[5]][$parents[6]]['mapping']);
  return $form[$parents[0]][$parents[1]][$parents[2]][$parents[3]][$parents[4]][$parents[5]][$parents[6]]['mapping'];
}

/**
 * Helper function that returns list of icons.
 */
function fr_dataset_field_get_icons() {
  return array(
    'warning' => array('classes' => array('fa', 'fa-warning')),
    'user' => array('classes' => array('fa', 'fa-user')),
    'group' => array('classes' => array('fa', 'fa-group')),
    'lock' => array('classes' => array('fa', 'fa-lock')),
    'unlock-alt' => array('classes' => array('fa', 'fa-unlock-alt')),
    'star' => array('classes' => array('fa', 'fa-star')),
    'picture-o' => array('classes' => array('fa', 'fa-picture-o')),
    'flag' => array('classes' => array('fa', 'fa-flag')),
    'exclamation-circle' => array('classes' => array('fa', 'fa-exclamation-circle')),
    'check-circle' => array('classes' => array('fa', 'fa-check-circle')),
    'credit-card' => array('classes' => array('fa', 'fa-credit-card')),
    'download' => array('classes' => array('fa', 'fa-download')),
  );
}

/**
 * Helper function that returns list of icons.
 */
function fr_dataset_field_get_icon_info($icon_code) {
  $icons = fr_dataset_field_get_icons();
  if (isset($icons[$icon_code])) {
    return $icons[$icon_code];
  }
  return NULL;
}

/**
 * Theme function for filters table.
 */
function theme_dataset_table_icons_mapping($variables) {
  $form = $variables['item'];

  $header = array(
    array('data' => t('Operator'), 'class' => array('icon-mapping-operator')),
    array('data' => t('Value'), 'class' => array('icon-mapping-value')),
    array('data' => t('Icon'), 'class' => array('icon-mapping-icon')),
    array('data' => t('Icon color'), 'class' => array('icon-mapping-icon-color')),
    array('data' => t('Icon placement'), 'class' => array('icon-mapping-icon-placement')),
    array('data' => t('Remove mapping'), 'class' => array('icon-mapping-remove')),
  );

  $rows = array();
  foreach (element_children($form) as $field) {
    $element = &$form[$field];

    $row = array();
    $row[] = array('data' => drupal_render($element['operator']), 'class' => array('icon-mapping-operator'));
    $row[] = array('data' => drupal_render($element['value']), 'class' => array('icon-mapping-value'));
    $row[] = array('data' => drupal_render($element['icon']), 'class' => array('icon-mapping-icon'));
    $row[] = array('data' => drupal_render($element['icon_color']), 'class' => array('icon-mapping-icon-color'));
    $row[] = array('data' => drupal_render($element['icon_placement']), 'class' => array('icon-mapping-icon-placement'));
    $row[] = drupal_render($element['remove']);

    $row = array_merge(array('data' => $row), $element['#attributes']);
    $rows[] = $row;
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'dataset-filters')));
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Callback to alter data before it goes to Google Charts.
 *
 * @param $display_type_info
 * @param $item
 * @param $data
 * @return mixed
 */
function fr_dataset_field_display_table_data_alter_callback($display_type_info, $item, $data) {
  $replacements_map = array();
  $icons_info = fr_dataset_field_get_icons();
  foreach ($data as $row_index => $row) {
    // Create replacements (tokens) map to be used in URL.
    foreach ($row as $column_index => $column) {
      $replacements_map['{' . $column['name'] . '}'] = $column['value'];
    }

    // Apply tokens.
    foreach ($row as $column_index => $column) {
      if (empty($item['display_settings']['overrides'])) {
        continue;
      }
      foreach ($item['display_settings']['overrides'] as $field_name => $overridden_field) {
        if ($column['name'] == $field_name && $overridden_field['enabled'] ) {
          // Override value as link.
          if ($overridden_field['type'] == 'link' && !empty($overridden_field['url'])) {
            $data[$row_index][$column_index]['overridden_value'] = l($data[$row_index][$column_index]['value'], str_replace(array_keys($replacements_map), $replacements_map, $overridden_field['url']));
          }
          // Override value with icon.
          elseif ($overridden_field['type'] == 'icon') {
            $value = &$data[$row_index][$column_index]['value'];
            $overridden_value = &$data[$row_index][$column_index]['overridden_value'];
            $overridden_value = "<!--$value-->$value";
            $apply_default = TRUE;

            foreach ($overridden_field['icons']['mapping'] as $mapping) {
              if ($mapping['operator'] != 'default' && fr_dataset_field_filter_calculate_value($mapping['value'],  $mapping['operator'],  $column['value'])) {
                $icon_info = $icons_info[$mapping['icon']];
                $overridden_value = fr_dataset_field_table_generate_icon($icon_info, $mapping, $value);
                $apply_default = FALSE;
                break;
              }
            }
            // Apply values for default icon.
            if ($apply_default) {
              foreach ($overridden_field['icons']['mapping'] as $mapping) {
                if ($mapping['operator'] == 'default') {
                  $icon_info = $icons_info[$mapping['icon']];
                  $overridden_value = fr_dataset_field_table_generate_icon($icon_info, $mapping, $value);
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  // View / Edit operations
  if (isset($item['display_settings']['available_operations']) && is_array($item['display_settings']['available_operations'])) {
    $primary = fr_dataset_field_table_get_primary_key($item['dataset']);
    if ($item['display_settings']['available_operations']['edit'] === 'edit') {
      foreach ($data as $data_key => $data_value) {
        $link_with_tokens = $item['display_settings']['edit_operation'];
        $token_names = array();
        foreach($data_value as $primary_key) {
          $token_names['{'.$primary_key['name'].'}'] = $primary_key['value'];
        }
        
        $link = str_replace(array_keys($token_names), $token_names, $link_with_tokens);
        $data[$data_key][] = array(
          'name' => t('Edit'),
          'type' => 'varchar',
          'value' => l(t('Edit'), $link),
        );
      }
    }

    if ($item['display_settings']['available_operations']['view'] === 'view') {
      foreach ($data as $data_key => $data_value) {

        $link_with_tokens = $item['display_settings']['view_operation'];
        $token_names = array();

        foreach($data_value as $primary_key) {
          $token_names['{'.$primary_key['name'].'}'] = $primary_key['value'];
        }

        $link = str_replace(array_keys($token_names), $token_names, $link_with_tokens);
        $data[$data_key][] = array(
          'name' => t('View'),
          'type' => 'varchar',
          'value' => l(t('View'), $link),
        );
      }
    }
  }

  return $data;
}

/**
 * Helper function to get primary key.
 *
 * @param $dataset - name of dataset for example: config.case_types
 * @return primary key name for example id or UserID
 */
function fr_dataset_field_table_get_primary_key($dataset) {
  $primary = FALSE;
  $data = new DataSetServiceClient();
  $dataset = $data->getStructure($dataset);
  if (isset($dataset['fields']) && is_array($dataset['fields'])) {
    $fields = $dataset['fields'];
    foreach ($fields as $key => $value) {
      if (isset($value['availability']) && strpos($value['availability'], 'primary') !== FALSE) {
        $primary = $value['name'];
      }
    }
  }
  return $primary;
}

/**
 * Helper function to generate icon HTML.
 *
 * @param $icon_info
 * @param $mapping
 * @param $value
 * @return string
 */
function fr_dataset_field_table_generate_icon($icon_info, $mapping, $value) {
  $output = "<!--$value-->";
  switch ($mapping['icon_placement']) {
     case 'replace':
       $output .= '<i style="color: ' . $mapping['icon_color'] . '" class="' . implode(' ', $icon_info['classes']) . '" title="' . $value . '"></i>';
       break;
     case 'before':
       $output .= '<i style="color: ' . $mapping['icon_color'] . '" class="' . implode(' ', $icon_info['classes']) . '" title="' . $mapping['icon'] . '"></i> ' . $value;
       break;
     case 'after':
       $output .= $value . ' <i style="color: ' . $mapping['icon_color'] . '" class="' . implode(' ', $icon_info['classes']) . '" title="' . $mapping['icon'] . '"></i> ';
       break;
   }
  return $output;
}

/**
 * Helper function to calculate values of filters.
 *
 * @param $filter_value
 * @param $operator
 * @param $real_value
 * @return bool
 */
function fr_dataset_field_filter_calculate_value($filter_value, $operator, $real_value) {
  switch ($operator) {
    case '=':
      return $filter_value == $real_value;
    case '!=':
      return $filter_value != $real_value;
    case '<':
      return $real_value < $filter_value;
    case '<=':
      return $real_value <= $filter_value;
    case '>=':
      return  $real_value >= $filter_value;
    case '>':
      return $real_value > $filter_value;
    case 'between':
      list($min, $max) = array_values($filter_value);
      return $real_value >= $min && $real_value <= $max;
    case 'contains':
      return fnmatch("*$filter_value*", $real_value);
    case 'not_contains':
      return !fnmatch("*$filter_value*", $real_value);
    case 'empty':
      return empty($real_value);
    case 'not_empty':
      return !empty($real_value);
    case 'is_true':
      return $real_value == TRUE;
    case 'is_false':
      return $real_value == FALSE;
  }
  return TRUE;
}
