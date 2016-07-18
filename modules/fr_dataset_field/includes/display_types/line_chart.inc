<?php
/**
 * @file
 * Helper functions for line chart.
 */

/**
 * Form callback for line chart settings.
 */
function fr_dataset_field_display_line_chart_settings_form(&$form, &$form_state, $submitted_values, $display_settings, $item, $delta) {
  if (isset($submitted_values['fields'])) {
    $fields = fr_dataset_field_parse_fields($submitted_values['fields']);
  }
  elseif (isset($item['fields'])) {
    $fields = unserialize($item['fields']);
  }
  else {
    $fields = array();
  }

  // Prepare options list and remove unchecked fields.
  $fields_options = array();
  foreach ($fields as $field_key => $field) {
    if ($field['enabled']) {
      $fields_options[$field_key] = $field_key;
    }
  }

  $element = array(
    'refresh_interval' => array(
      '#title' => t('Refresh interval'),
      '#type' => 'numberfield',
      '#field_suffix' => t('seconds'),
      '#min' => 15,
      '#description' => t('Specify how often report should be refreshed. Leave empty field not refresh the report at all. Minimum is %min seconds.', array('%min' => 15)),
      '#default_value' => isset($display_settings['refresh_interval']) ? $display_settings['refresh_interval'] : NULL,
    ),

    'x_field' => array(
      '#title' => t('X-Axis field'),
      '#type' => 'select',
      '#empty_option' => t('- Select field -'),
      '#description' => t('Chose field from list of enabled fields that will be used for x-axis.'),
      '#options' => $fields_options,
      '#required' => TRUE,
      '#default_value' => isset($display_settings['x_field']) ? $display_settings['x_field'] : NULL,
    ),

    'font_size' => array(
      '#title' => t('Font size'),
      '#type' => 'radios',
      '#options' => array('14' => 'default', '8' => '8', '10' => '10', '12' => '12', '16' => '16', '18' => '18', '20' => '20',),
      '#default_value' => isset($display_settings['font_size']) ? $display_settings['font_size'] : NULL,
      '#attributes' => array('class' => array('clearfix')),
    ),

    'font_style' => array(
      '#title' => t('Font style'),
      '#type' => 'radios',
      '#options' => array('0' => 'default', '1' => 'Bold', '2' => 'Italic', '3' => 'Bold and italic',),
      '#default_value' => isset($display_settings['font_style']) ? $display_settings['font_style'] : NULL,
      '#attributes' => array('class' => array('clearfix')),
    ),

    'title_haxis' => array(
      '#title' => t('Title for horizontal axis'),
      '#type' => 'textfield',
      '#default_value' => isset($display_settings['title_haxis']) ? $display_settings['title_haxis'] : NULL,
    ),

    'title_vaxis' => array(
      '#title' => t('Title for vertical axis'),
      '#type' => 'textfield',
      '#default_value' => isset($display_settings['title_vaxis']) ? $display_settings['title_vaxis'] : NULL,
    ),

    'min_axis_horizontal' => array(
      '#title' => t('Minimum value for horizontal axis'),
      '#type' => 'textfield',
      '#default_value' => isset($display_settings['min_axis_horizontal']) ? $display_settings['min_axis_horizontal'] : NULL,
    ),

    'min_axis_vertical' => array(
      '#title' => t('Minimum value for vertical axis'),
      '#type' => 'textfield',
      '#default_value' => isset($display_settings['min_axis_vertical']) ? $display_settings['min_axis_vertical'] : NULL,
    ),

    'max_axis_horizontal' => array(
      '#title' => t('Maximum value for horizontal axis'),
      '#type' => 'textfield',
      '#default_value' => isset($display_settings['max_axis_horizontal']) ? $display_settings['max_axis_horizontal'] : NULL,
    ),

    'max_axis_vertical' => array(
      '#title' => t('Maximum value for vertical axis'),
      '#type' => 'textfield',
      '#default_value' => isset($display_settings['max_axis_vertical']) ? $display_settings['max_axis_vertical'] : NULL,
    ),

    'legend_position' => array(
      '#title' => t('Legend position'),
      '#type' => 'radios',
      '#default_value' => isset($display_settings['legend_position']) ? $display_settings['legend_position'] : 'bottom',
      '#options' => array(
        'bottom' => 'bottom',
        'right' => 'right',
        'top' => 'top',
        'left' => 'left',
      ),
      '#attributes' => array('class' => array('clearfix')),
    ),

    'column_thickness' => array(
      '#title' => t('Column/Bar thickness'),
      '#type' => 'radios',
      '#options' => array(
        '1' => 'default',
        '0.25' => 'x0.25',
        '0.5' => 'x0.5',
        '0.75' => 'x0.75',
        '1.25' => 'x1.25',
        '1.5' => 'x1.5',
        '1.75' => 'x1.75',
        '2' => 'x2',
        '3' => 'x3',
        '5' => 'x5',
        '10' => 'x10',
      ),
      '#default_value' => isset($display_settings['column_thickness']) ? $display_settings['column_thickness'] : '1',
      '#attributes' => array('class' => array('clearfix')),
    ),

    'background' => array(
      '#title' => t('Background color'),
      '#type' => 'colorpicker',
      '#default_value' => $display_settings['background'],
      '#attributes' => array('class' => array('clearfix')),
    ),

    'textcolor' => array(
      '#title' => t('Text color'),
      '#type' => 'colorpicker',
      '#default_value' => isset($display_settings['textcolor']) ? $display_settings['textcolor'] : '#ffffff',
      '#attributes' => array('class' => array('clearfix')),
    ),

    'bars_color' => array(
      '#title' => t('Color of bars'),
      '#type' => 'fieldset',
      '#attributes' => array('class' => array('bars-color')),
    ),

    'chart_area' => array(
      '#title' => t('Chart area'),
      '#type' => 'fieldset',
      '#attributes' => array('class' => array('chart-area')),
      '#description' => t('Chart area is only the chart itself excluding legend and axis. Available values for each field from 0 to 100.'),

      'width' => array(
        '#title' => t('Width'),
        '#type' => 'numberfield',
        '#field_suffix' => '%',
        '#min' => 0,
        '#max' => 100,
        '#default_value' => isset($display_settings['chart_area']['width']) ? $display_settings['chart_area']['width'] : NULL,
      ),

      'height' => array(
        '#title' => t('Height'),
        '#type' => 'numberfield',
        '#field_suffix' => '%',
        '#min' => 0,
        '#max' => 100,
        '#default_value' => isset($display_settings['chart_area']['height']) ? $display_settings['chart_area']['height'] : NULL,
      ),

      'top' => array(
        '#title' => t('Margin top'),
        '#type' => 'numberfield',
        '#field_suffix' => '%',
        '#min' => 0,
        '#max' => 100,
        '#default_value' => isset($display_settings['chart_area']['top']) ? $display_settings['chart_area']['top'] : NULL,
      ),

      'left' => array(
        '#title' => t('Margin left'),
        '#type' => 'numberfield',
        '#field_suffix' => '%',
        '#min' => 0,
        '#max' => 100,
        '#default_value' => isset($display_settings['chart_area']['left']) ? $display_settings['chart_area']['left'] : NULL,
      ),
    ),
  );

  $i = 0;
  $default_colors = array(
    '#3366cc', '#dc3912', '#ff9900', '#109618', '#990099', '#0099c6', '#dd4477', '#66aa00', '#b82e2e', '#316395', '#994499', '#22aa99', '#aaaa11', '#6633cc', '#e67300', '#8b0707', '#651067', '#329262', '#5574a6', '#3b3eac', '#b77322', '#16d620', '#b91383', '#f4359e', '#9c5935', '#a9c413', '#2a778d', '#668d1c', '#bea413', '#0c5922', '#743411',
  );

  foreach ($fields_options as $key => $value) {
    $element['bars_color'] += array(
      $key => array(
        '#title' => t($value.' bar color'),
        '#type' => 'colorpicker',
        '#attributes' => array('class' => array('clearfix')),
        '#default_value' => isset($display_settings['bars_color'][$key]) ? $display_settings['bars_color'][$key] : $default_colors[$i],
      ),
    );
    $i++;
  }
  return $element;
}
