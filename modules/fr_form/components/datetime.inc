<?php

/**
 * @file
 * Extension of webform module - datetime component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_datetime() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'required' => 0,
    'extra' => array(
      'timezone' => 'user',
      'start_date' => '-2 years',
      'end_date' => '+2 years',
      'year_textfield' => 0,
      'datepicker' => 1,
      'title_display' => 0,
      'description' => '',
      'private' => FALSE,
      'analysis' => FALSE,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_datetime() {
  return array(
    'webform_display_datetime' => array(
      'render element' => 'element',
      'path' => drupal_get_path('module', 'fr_form'),
      'file' => 'components/datetime.inc',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_datetime($component) {
  $form = array();
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $component['value'],
    '#description' => t('The default value of the field.') . '<br />' . t('Accepts any date in any <a href="http://www.gnu.org/software/tar/manual/html_chapter/Date-input-formats.html">GNU Date Input Format</a>. Strings such as today, +2 months, and Dec 9 2004 are all valid.'),
    '#size' => 60,
    '#maxlength' => 127,
    '#weight' => 0,
  );
  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_datetime($component, $value = NULL, $filter = TRUE) {
  drupal_add_library('fr_form', 'jquery_timepicker_addon');
  drupal_add_js(drupal_get_path('module', 'fr_form').'/js/fr_form_timepicker.js');

  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;

  $element = array(
    '#type' => 'textfield',
    '#title' => $filter ? webform_filter_xss($component['name']) : $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#description' => $filter ? webform_filter_descriptions($component['extra']['description'], $node) : $component['extra']['description'],
    '#required' => $component['required'],
    '#default_value' => $filter ? webform_replace_tokens($component['value'], $node) : $component['value'],
    '#weight' => $component['weight'],
    '#prefix' => '<div class="webform-component-datetime-field" id="webform-component-' . $component['form_key'] . '">',
    '#suffix' => '</div>',
  );

  return $element;
}

/**
 * Implements _webform_submit_component().
 */
function _webform_submit_datetime($component, $value) {
  return $value;
}

/**
 * Implements hook_library().
 */
function fr_form_library() {
  //jQuery UI Timepicker addon
  $path = drupal_get_path('module', 'fr_form');

  $library['jquery_timepicker_addon'] = array(
    'title' => t('jQuery UI Timepicker addon'),
    'website' => 'https://github.com/trentrichardson/jQuery-Timepicker-Addon',
    'version' => '1.5.5',
    'js' => array(
      array('data' => libraries_get_path('jquery_timepicker_addon') . '/src/jquery-ui-timepicker-addon.js', 'type' => 'file'),
      array('data' => libraries_get_path('jquery_timepicker_addon') . '/src/jquery-ui-sliderAccess.js', 'type' => 'file'),
    ),
    'css' => array(
      array('data' => libraries_get_path('jquery_timepicker_addon') . '/src/jquery-ui-timepicker-addon.css'),
    ),
    'dependencies' => array(
      array('system', 'ui'),
      array('system', 'ui.datepicker'),
      array('system', 'ui.slider'),
    ),
  );

  return $library;
}
