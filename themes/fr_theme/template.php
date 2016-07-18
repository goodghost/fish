<?php 
/**
 * Override or insert variables into the page template.
 */
function fr_theme_preprocess_page(&$vars) {
  if (isset($vars['node'])) {
    $node = $vars['node'];
  }

  if ((isset($node) && $node->type == "dashboard") || (isset($node) && $node->type == "wallboard")) {
    drupal_add_js(drupal_get_path('theme', 'fr_theme').'/js/common.js');
  }

  drupal_add_css(drupal_get_path('theme', 'fr_theme').'/css/overrides-static.css', array('group' => 100, 'weight' => 1));
  drupal_add_css(drupal_get_path('theme', 'fr_theme').'/css/overrides.css', array('group' => 100, 'weight' => 2));

  // Add welcome message to theme.
  $vars['welcome_message'] = variable_get('site_welcome_message');

  $theme = $vars['theme_hook_suggestions'];

  // Change page title for user login form.
  if (in_array('page__user', $theme) && in_array('page__front', $theme) && count($theme) == 2) {
    unset($vars['primary_local_tasks']['#primary']);
    $vars['title'] = '';
    $vars['page_title'] = t('<span>Login</span> panel');
  }
  // Change page title for user password reset form.
  elseif (fnmatch('user/password', current_path())) {
    $vars['title'] = '';
    $vars['page_title'] = t('<span>Reset</span> password');
  }
}


function fr_theme_preprocess_node(&$vars) {
  if ($vars['type'] == 'webform' && isset($vars['fr_form_object'])){
    $vars['classes_array'][] = 'webform-api';
  }
}


/**
 * Hide teaser when previewing nodes.
 */
function fr_theme_node_preview($variables) {
  $node = $variables['node'];

  $output = '<div class="preview">';

  $elements = node_view($node, 'full');
  $full = drupal_render($elements);

  $output .= '<h3>' . t('Preview full version') . '</h3>';
  $output .= $full;
  $output .= "</div>\n";

  return $output;
}
