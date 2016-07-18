<?php
/**
 * @file
 * fr_core.features.language.inc
 */

/**
 * Implements hook_locale_default_languages().
 */
function fr_core_locale_default_languages() {
  $languages = array();

  // Exported language: en-US.
  $languages['en-US'] = array(
    'language' => 'en-US',
    'name' => 'American English',
    'native' => 'American English',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'en-us',
    'weight' => 0,
  );
  return $languages;
}
