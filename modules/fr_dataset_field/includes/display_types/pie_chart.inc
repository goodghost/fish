<?php
/**
 * @file
 * Helper functions for pie chart.
 */

/**
 * Form callback for pie chart settings.
 */
function fr_dataset_field_display_pie_chart_settings_form(&$form, &$form_state, $submitted_values, $display_settings, $item, $delta) {
  $current_data = array();
  if (isset($submitted_values['fields'])) {
    $fields = fr_dataset_field_parse_fields($submitted_values['fields']);
    foreach ($fields as $key => $field) {
      if ($fields[$key]['enabled'] != 0) {
        $current_data[$key] = $key;
      }
    }
  }
  elseif (isset($item['fields'])) {
    $fields = unserialize($item['fields']);
    foreach ($fields as $key => $field) {
      if ($fields[$key]['enabled'] != 0) {
        $current_data[$key] = $key;
      }
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

    'is_third_dim' => array(
      '#title' => t('3D view'),
      '#type' => 'checkbox',
      '#default_value' => isset($display_settings['is_third_dim']) ? $display_settings['is_third_dim'] : NULL,
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

    'background' => array(
      '#title' => t('Background color'),
      '#type' => 'colorpicker',
      '#default_value' => isset($display_settings['background']) ? $display_settings['background'] : NULL,
    ),

    'textcolor' => array(
      '#title' => t('Text color'),
      '#type' => 'colorpicker',
      '#default_value' => isset($display_settings['textcolor']) ? $display_settings['textcolor'] : NULL,
      '#attributes' => array('class' => array('clearfix')),
    ),

    'slices_colors' => array(
      '#title' => t('Color of slices'),
      '#type' => 'fieldset',
      '#attributes' => array('class' => array('slices-colors')),
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

  foreach ($current_data as $key => $value) {
    $element['slices_colors'] += array(
      $key => array(
        '#title' => t($value.' slice color'),
        '#type' => 'colorpicker',
        '#attributes' => array('class' => array('clearfix')),
        '#default_value' => isset($display_settings['slices_colors'][$key]) ? $display_settings['slices_colors'][$key] : $default_colors[$i],
      ),
    );
    $i++;
  }
  return $element;
}
