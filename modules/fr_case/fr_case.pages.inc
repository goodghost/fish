<?php

////////////////////////////////////////////////////////////////////////////////
// Case.
////////////////////////////////////////////////////////////////////////////////

/**
 * Title callback: Returns the title of the case.
 */
function fr_case_page_title($case) {
  if (isset($case['reference'])) {
    $case_ref = $case['reference'];
  }
  elseif (isset($case['scenes'][0]['soc_ref'])) {
    $case_ref = $case['scenes'][0]['soc_ref'];
  }

  if (isset($case_ref)) {
    return t('Case: @case', array('@case' => $case_ref));
  }
  else {
    return t('Case');
  }
}

/**
 * Menu callback: Displays a single case.
 */
function fr_case_page_view($case) {
  if (!$case) {
    return MENU_NOT_FOUND;
  }

  drupal_set_title(fr_case_page_title($case));

  $properties = array(
    t('GPMS Status') => isset($case['gpms_status']) ? $case['gpms_status'] : t('N/A'),
    t('Crime Type') => isset($case['case_type']) ? $case['case_type'] : t('N/A'),
    t('Evidence Volume') => isset($case['num_exhibits']) ? $case['num_exhibits'] : t('N/A'),
    t('Case Generation Date') => isset($case['case_date']) ? $case['case_date'] : t('N/A'),
    t('Case Creator') => isset($case['case_owner']) ? $case['case_owner'] : t('N/A'),
  );

  $rows = array();
  foreach ($properties as $key => $value) {
    $rows[] = array(array('data' => $key, 'class' => drupal_html_class($key)), $value);
  }

  $case_info = array(
    '#theme' => 'table',
    '#rows' => $rows,
  );

  $images_host = variable_get('fr_case_images_hostname', 'http://213.212.70.93');
  $scenes = array();
  foreach ($case['scenes'] as $scene_index => $scene) {
    $scenes[] = array(
      'name' => $scene['scene_name'],
      'scene_url' => url('cases/' . $scene['project_id'] . '/scenes/' . $scene_index),
      'thumbnail_url' => url($images_host . $scene['thumbnail_url']),
    );
  }

  return array(
    '#theme' => 'fr_case',
    '#case' => $case,
    '#case_info' => $case_info,
    '#scenes' => $scenes,
  );
}

////////////////////////////////////////////////////////////////////////////////
// Scene: View.
////////////////////////////////////////////////////////////////////////////////

/**
 * Title callback: Returns the title of the case.
 */
function fr_case_scene_page_title($case, $scene) {
  return $scene['scene_name'];
}

/**
 * Menu callback: Displays a case scene.
 */
function fr_case_scene_page_form($form, &$form_state, $case, $scene) {
  global $base_path;

  $case_title = fr_case_page_title($case);
  drupal_set_title(t('@case/@scene', array('@case' => $case_title, '@scene' => $scene['scene_name'])));

  $form['#attributes']['id'] = 'fr-case-scene-dockets-form';

  // Scene images.
  $dockets = array();
  $images_host = variable_get('fr_case_images_hostname', 'http://213.212.70.93');

  try {
    $client = new CaseServiceClient();
    $result = $client->getSceneDockets($scene['project_id'], $scene['id']);
  }
  catch (Exception $e) {
    watchdog_exception('fr_case', $e);
    form_set_error('', 'Unknown error occurred. Please contact administrator.');
    return array();
  }

  if (empty($result['scenedetails'])) {
    form_set_error('', 'No dockets available.');
    return array();
  }

  $print_links = array();
  $is_remote = fr_user_is_remote();

  foreach ($result['scenedetails'] as $docket_label => $docket) {
    if (!$docket_label) {
      $docket_label = t('Docket');
    }
    
    $print_links[$docket_label] = $base_path.'cases/'.$case['case_id'].'/scenes/'.$scene['id'].'/print/new/'.$docket_label;

    $dockets[$docket_label] = array();
    foreach ($docket as $docket_image) {
      $image = array(
        'id' => $docket_image['id'],
        'category' => $docket_image['category'],
        'category_class' => fr_case_scene_image_get_category_class($docket_image['category']),
        'order' => $docket_image['order'],
        'user_id' => $docket_image['user_id'],
        'ref' => $docket_image['ref'],
        'type' => $docket_image['type'],
        'sensitive' => $docket_image['sensitive'],
        'restricted' => $docket_image['restricted'],
        'thumbnail_url' => url($images_host . $docket_image['thumbnail']),
        'screensize_url' => url($images_host . $docket_image['screensize']),
        'access' => TRUE,
        'image_info' => $scene['soc_ref'] . '/' . (intval($scene['id']) + 1) . '/' . $docket_label . '/',
      );
      if ($image['restricted'] && !user_access('view scene restricted images')) {
        $image['access'] = FALSE;
      }
      $dockets[$docket_label][] = $image;
    }
  }

  // Sort dockets alphabetically by docket label (array key).
  uksort($dockets, 'strcasecmp');
  $dockets_original = $dockets;

  // Apply filters.
  if (isset($form_state['values'])) {
    $values = &$form_state['values'];

    // Filter by docket.
    if ($values['docket']) {
      foreach ($dockets as $docket_label => $docket) {
        if ($docket_label != $values['docket']) {
          unset($dockets[$docket_label]);
        }
      }
    }

    // Filter by user.
    if ($values['user']) {
      foreach ($dockets as $docket_label => $docket) {
        foreach ($docket as $image_index => $docket_image) {
          if ($docket_image['user_id'] != $values['user']) {
            unset($dockets[$docket_label][$image_index]);
          }
        }
        if (empty($dockets[$docket_label])) {
          unset($dockets[$docket_label]);
        }
      }
    }
  }

  // Count images in dockets.
  $total_images = 0;
  foreach ($dockets as $docket_label => $docket) {
    $total_images += count($docket);
  }

  // Form.
  $form['#attached'] = array(
    'library' => array(
      array('fr_case', 'jquery_lazyload_integration'),
      array('fr_case', 'photoswipe'),
      array('fr_case', 'tooltip'),
      array('mediaelement', 'mediaelement'),
    ),
  );

  // Options.
  $form['options'] = array(
    '#title' => t('Filters'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Prepare options for filters.
  $docket_options = array();
  $docket_users = array();
  foreach ($dockets_original as $docket_label => $docket) {
    $docket_options[$docket_label] = $docket_label;
    foreach ($docket as $docket_image) {
      $docket_users[$docket_image['user_id']] = $docket_image['user_id'];
    }
  }
  $docket_options = array('' => t('All')) + $docket_options;
  $docket_users = array('' => t('All')) + $docket_users;

  // Filter by user.
  $form['options']['user'] = array(
    '#type' => 'radios',
    '#options' => $docket_users,
    '#title' => t('Filter by user'),
    '#default_value' => '',
    '#ajax' => array(
      'callback' => 'fr_case_scene_dockets_display_ajax_callback',
      'wrapper' => 'case-scene-dockets-wrapper',
      'progress' => array('type' => 'none'),
      'effect' => 'fade',
    ),
  );

  // Filter by docket.
  $form['options']['docket'] = array(
    '#type' => 'radios',
    '#options' => $docket_options,
    '#title' => t('Filter by docket'),
    '#default_value' => '',
    '#ajax' => array(
      'callback' => 'fr_case_scene_dockets_display_ajax_callback',
      'wrapper' => 'case-scene-dockets-wrapper',
      'progress' => array('type' => 'none'),
      'effect' => 'fade',
    ),
  );

  $form['actions'] = array(
    '#type' => 'item',
    '#weight' => -1,
  );

  // Switch scene dropdown.
  $scene_switch_options = array();
  foreach ($case['scenes'] as $scene_index => $scene_details) {
    $case_id = $scene_details['project_id'];
    $scene_switch_options["cases/$case_id/scenes/$scene_index"] = $scene_details['scene_name'];
  }
  $form['actions']['switch_scene'] = array(
    '#type' => 'select',
    '#options' => $scene_switch_options,
    '#title' => t('Switch scene'),
    '#default_value' => current_path(),
    '#weight' => 1,
    '#ajax' => array(
      'callback' => 'fr_case_scene_switch_ajax_callback',
      'progress' => array('type' => 'none'),
    ),
  );

  $form['display_dockets'] = array(
    '#theme' => 'fr_case_scene_dockets',
    '#case' => $case,
    '#scene' => $scene,
    '#total_images' => $total_images,
    '#dockets' => $dockets,
    '#video' => fr_case_video(),
    '#print_links' => $print_links,
    '#is_remote' => $is_remote,
  );

  $default_restricted_image = $base_path . drupal_get_path('theme', 'fr_theme') . '/images/default_restricted_image.png';
  drupal_add_js(array('mediaelementAll' => TRUE), array('type' => 'setting'));
  $js_settings = array(
    'dockets' => $dockets,
    'default_restricted_image' => $default_restricted_image,
  );

  $form['display_dockets']['#attached']['js'][] = array(
    'data' => array('fr_case' => $js_settings),
    'type' => 'setting',
  );

  $form['actions']['slideshow'] = array(
    '#type' => 'item',
    '#markup' => t('Scene slideshow'),
  );

  $form['actions']['back_to_case'] = array(
    '#type' => 'item',
    '#markup' => l(t('Back to case'), "cases/$case_id"),
  );

  return $form;
}

////////////////////////////////////////////////////////////////////////////////
// Image data (exif).
////////////////////////////////////////////////////////////////////////////////

/**
 * Menu callback: Return scene image details.
 */
function fr_case_scene_image_data($image_id) {
  $image_data = array();
  try {
    $client = new ImageDataServiceClient();
    $data = $client->getImageDataById($image_id);

    if (!empty($data['imagedata'])) {
      $exif = $data['imagedata']['exif'];
      $notes = $data['imagedata']['notes'];
      $image_data['exif'] = theme('definition_list', array('items' => $exif));
      $image_data['notes'] = theme('definition_list', array('items' => $notes));
      return json_encode($image_data);
    }
    else {
      return t('No information found.');
    }
  }
  catch (Exception $e) {
    watchdog_exception('fr_case_image_data', $e);
  }
}
