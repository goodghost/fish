<?php
/**
 * @file
 * Helper functions for gauge.
 */

/**
 * Form callback for line chart settings.*/
function fr_dataset_field_display_gauge_settings_form(&$form, &$form_state, $submitted_values, $display_settings, $item, $delta) {
  $element = array(
    'refresh_interval' => array(
      '#title' => t('Refresh interval'),
      '#type' => 'numberfield',
      '#field_suffix' => t('seconds'),
      '#min' => 15,
      '#description' => t('Specify how often report should be refreshed. Leave empty field to not refresh the report at all. Minimum is %min seconds.', array('%min' => 15)),
      '#default_value' => isset($display_settings['refresh_interval']) ? $display_settings['refresh_interval'] : NULL,
    ),
    'width' => array(
      '#title' => t('Width of each gauge'),
      '#type' => 'numberfield',
      '#default_value' => isset($display_settings['width']) ? $display_settings['width'] : NULL,
    ),
    'height' => array(
      '#title' => t('Height of each gauge'),
      '#type' => 'numberfield',
      '#default_value' => isset($display_settings['height']) ? $display_settings['height'] : NULL,
    ),
    'max' => array(
      '#title' => t('Maximal value'),
      '#description' => t('The maximal value of a gauge.'),
      '#type' => 'numberfield',
      '#default_value' => isset($display_settings['max']) ? $display_settings['max'] : NULL,
    ),
    'yellowFrom' => array(
      '#title' => t('Yellow from'),
      '#type' => 'numberfield',
      '#descripton' => t('The lowest value for a range marked by a yellow color. Leave empty to hide red area.'),
      '#default_value' => isset($display_settings['yellowFrom']) ? $display_settings['yellowFrom'] : NULL,
    ),
    'yellowTo' => array(
      '#title' => t('Yellow to'),
      '#type' => 'numberfield',
      '#descripton' => t('The highest value for a range marked by a yellow color. Leave empty to hide red area.'),
      '#default_value' => isset($display_settings['yellowTo']) ? $display_settings['yellowTo'] : NULL,
    ),
    'redFrom' => array(
      '#title' => t('Red from'),
      '#type' => 'numberfield',
      '#descripton' => t('The lowest value for a range marked by a red color. Leave empty to hide red area.'),
      '#default_value' => isset($display_settings['redFrom']) ? $display_settings['redFrom'] : NULL,
    ),
    'redTo' => array(
      '#title' => t('Red to'),
      '#type' => 'numberfield',
      '#descripton' => t('The highest value for a range marked by a red color.. Leave empty to hide red area.'),
      '#default_value' => isset($display_settings['redTo']) ? $display_settings['redTo'] : NULL,
    ),
  );
  return $element;
}
