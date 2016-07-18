<?php
/**
 * @file
 * Contains mocks for Drupal API.
 */

require_once 'http_client/includes/HttpClient.inc';
require_once 'http_client/includes/HttpClientCurlDelegate.inc';
require_once 'http_client/includes/HttpClientOAuth.inc';

require_once 'kis_services_feature/includes/ServiceClient.inc';
require_once 'kis_services_feature/includes/KisServicesException.inc';
require_once 'kis_services_feature/includes/HttpClientJSONFormatter.inc';
require_once 'kis_services_feature/includes/KisServiceClientAuth.inc';

global $conf;
require_once '/vagrant/settings/settings.services.dev.php';

define('WATCHDOG_EMERGENCY', 0);
define('WATCHDOG_ALERT', 1);
define('WATCHDOG_CRITICAL', 2);
define('WATCHDOG_ERROR', 3);
define('WATCHDOG_WARNING', 4);
define('WATCHDOG_NOTICE', 5);
define('WATCHDOG_INFO', 6);
define('WATCHDOG_DEBUG', 7);
define('REQUEST_TIME', (int) $_SERVER['REQUEST_TIME']);
define('LANGUAGE_NONE', 'und');


// Mock Drupal API functions used by service classes
function watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL) {}

function check_plain($text) {
  return $text;
}

function variable_get($name, $default = NULL) {
  global $conf;

  return isset($conf[$name]) ? $conf[$name] : $default;
}

function t($string, array $args = array(), array $options = array()) {
  return $string;
}

function cache_set($cid, $data, $bin = 'cache', $expire = CACHE_PERMANENT) {}

function cache_get($cid, $bin = 'cache') {
  return NULL;
}

function drupal_static($name, $default_value = NULL, $reset = FALSE) {
  return NULL;
}

/**
 * Converts a PHP variable into its JavaScript equivalent.
 *
 * We use HTML-safe strings, with several characters escaped.
 *
 * @see drupal_json_decode()
 * @see drupal_json_encode_helper()
 * @ingroup php_wrappers
 */
function drupal_json_encode($var) {
  // The PHP version cannot change within a request.
  static $php530;

  if (!isset($php530)) {
    $php530 = version_compare(PHP_VERSION, '5.3.0', '>=');
  }

  if ($php530) {
    // Encode <, >, ', &, and " using the json_encode() options parameter.
    return json_encode($var, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
  }

  // json_encode() escapes <, >, ', &, and " using its options parameter, but
  // does not support this parameter prior to PHP 5.3.0.  Use a helper instead.
  include_once DRUPAL_ROOT . '/includes/json-encode.inc';
  return drupal_json_encode_helper($var);
}

/**
 * Converts an HTML-safe JSON string into its PHP equivalent.
 *
 * @see drupal_json_encode()
 * @ingroup php_wrappers
 */
function drupal_json_decode($var) {
  return json_decode($var, TRUE);
}

function console($var) {
  fwrite(STDERR, print_r($var, TRUE));
}

function commerce_order_load($order_id) {
}

function commerce_order_save($order) {
}

function drupal_alter($type, &$data, &$context1 = NULL, &$context2 = NULL, &$context3 = NULL) {
}

function dpm($input, $name = NULL, $type = 'status') {
  if ($name) {
    console(strtoupper($name) . "\n--------------------------\n$input");
  }
  else {
    console($input);
  }
}
