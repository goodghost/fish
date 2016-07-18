<?php

/**
 * Filter value element for text operators.
 */
function fr_dataset_field_filter_value_single_textfield_element($default_value = NULL) {
  return array(
    '#type' => 'textfield',
    '#title' => t('Filter value'),
    '#title_display' => 'invisible',
    '#size' => 20,
    '#default_value' => $default_value,
  );
}

/**
 * Filter value element for numeric operators.
 */
function fr_dataset_field_filter_value_single_number_element($default_value = NULL) {
  return array(
    '#type' => 'numberfield',
    '#title' => t('Filter value'),
    '#title_display' => 'invisible',
    '#size' => 20,
    '#default_value' => $default_value,
  );
}

/**
 * Filter value element for date operators.
 */
function fr_dataset_field_filter_value_single_date_element($default_value = NULL) {
  return array(
    '#title' => t('Filter value'),
    '#title_display' => 'invisible',
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d',
    '#date_label_position' => 'invisible',
    '#date_year_range' => '-10:+1',
    '#default_value' => $default_value,
  );
}

/**
 * Filter value element for date range operator.
 */
function fr_dataset_field_filter_value_range_date_element($default_value = NULL) {
  return array(
    '#type' => 'item',
    '#tree' => true,
    'value1' => array(
      '#title' => t('Start date'),
      '#type' => 'date_popup',
      '#date_format' => 'Y-m-d',
      '#date_label_position' => 'invisible',
      '#date_year_range' => '-10:+1',
      '#default_value' => $default_value['value1'],
    ),
    'value2' => array(
      '#title' => t('End date'),
      '#type' => 'date_popup',
      '#date_format' => 'Y-m-d',
      '#date_label_position' => 'invisible',
      '#date_year_range' => '-10:+1',
      '#default_value' => $default_value['value2'],
    ),

  );
}

/**
 * Filter value element for numeric range operator.
 */
function fr_dataset_field_filter_value_range_number_element($default_value = NULL) {
  return array(
    '#type' => 'item',
    '#tree' => true,
    'value1' => array(
      '#title' => t('Min'),
      '#type' => 'numberfield',
      '#size' => 20,
      '#default_value' => $default_value['value1'],
    ),
    'value2' => array(
      '#title' => t('Max'),
      '#type' => 'numberfield',
      '#size' => 20,
      '#default_value' => $default_value['value2'],
    ),

  );
}

/**
 * Filter value element for date range operator.
 */
function fr_dataset_field_filter_value_range_datetime_element($default_value = NULL) {
  return array(
    '#type' => 'item',
    '#tree' => true,
    'value1' => array(
      '#title' => t('Start date'),
      '#type' => 'date_popup',
      '#date_format' => DATE_ISO8601,
      '#date_label_position' => 'invisible',
      '#date_year_range' => '-10:+1',
      '#default_value' => $default_value['value1'],
    ),
    'value2' => array(
      '#title' => t('End date'),
      '#type' => 'date_popup',
      '#date_format' => DATE_ISO8601,
      '#date_label_position' => 'invisible',
      '#date_year_range' => '-10:+1',
      '#default_value' => $default_value['value2'],
    ),
  );
}

/**
 * Filter value element for datetime operators.
 */
function fr_dataset_field_filter_value_single_datetime_element($default_value = NULL) {
  return array(
    '#title' => t('Filter value'),
    '#title_display' => 'invisible',
    '#type' => 'date_popup',
    '#date_format' => DATE_ISO8601,
    '#date_year_range' => '-10:+1',
    '#default_value' => $default_value,
  );
}
