<?php

module_load_include('inc', 'fr_case', 'fr_case.pages');

/**
 * Menu callback: Print request management form.
 */
function fr_print_request_manage_page($case, $scene) {
  $case_title = fr_case_page_title($case);
  drupal_set_title(t('Print requests - @case/@scene', array('@case' => $case_title, '@scene' => $scene['scene_name'])));

  $print_requests = fr_print_request_load_all_for_scene($case['case_id'], $scene['id']);

  $header = array(
    t('Print copies'),
    t('Product'),
    t('Delivery Type'),
    t('Urgency'),
    t('Target Date'),
    t('Requesting Officer'),
    t('Delivery Address'),
    t('Requested by'),
    t('Docket'),
    t('Status'),
    t('Actions'),
  );

  $rows = array();

  foreach ($print_requests as $i => $print_request) {
    if (fr_user_get_username() == $print_request['user_name'] || user_access('approve print requests') || user_access('reject print requests') || user_access('edit any print request')) {

      $rows[$i] = array(
        $print_request['prints'],
        $print_request['print_product'],
        $print_request['delivery_type'],
        $print_request['urgency'],
        $print_request['target_date'],
        $print_request['requesting_officer'],
        $print_request['delivery_address'],
        $print_request['user_name'],
        $print_request['docket'],
        $print_request['status'],
        '', // Actions
      );

      $print_request_url = fr_print_request_get_url($case, $scene, $print_request);

      // Link to approve print request.
      if (fr_print_request_approve_access($case, $scene, $print_request)) {
        $rows[$i][10] .= l('approve', "$print_request_url/approve") . ' ';
      }

      // Link to reject print request.
      if (fr_print_request_reject_access($case, $scene, $print_request)) {
        $rows[$i][10] .= l('reject', "$print_request_url/reject") . ' ';
      }

      // Link to edit print request.
      if (fr_print_request_edit_access($case, $scene, $print_request)) {
        $rows[$i][10] .= l('edit', "$print_request_url/edit") . ' ';
      }
    }
  }
  $output = '';
  if (empty($rows)) {
    $output = t("No print requests for this case were ordered or you don't have access to view this information.");
  } else {
    $output = theme('table', array('header' => $header, 'rows' => $rows));
  }
  return $output;
}

/**
 * Menu callback: Scene album print request form.
 */
function fr_print_request_form($form, &$form_state, $case, $scene, $print_request = NULL, $docket_name = NULL) {

  $docket_default_value = '';

  // Get scene dockets.
  $client = new CaseServiceClient();
  $result = $client->getSceneDockets($case['case_id'], $scene['id']);
  $dockets = array();
  foreach ($result['scenedetails'] as $docket_label => $docket) {
    $dockets[$docket_label] = $docket_label;
  }

  $editing = !empty($print_request);

  // Set default docket value
  if (!$print_request && !empty($docket_name)) {
    $docket_default_value = $docket_name;
  } else if (isset($print_request['docket'])) {
    $docket_default_value = $print_request['docket'];
  } else {
    $docket_default_value = current($dockets);
  }

  $case_title = fr_case_page_title($case);
  drupal_set_title(t($editing ? 'Edit print request - @case/@scene' : 'New print request - @case/@scene', array('@case' => $case_title, '@scene' => $scene['scene_name'])));

  $form['docket'] = array(
    '#title' => t('Docket'),
    '#type' => 'radios',
    '#options' => $dockets,
    '#default_value' => $docket_name,
    '#disabled' => $editing,
    '#required' => TRUE,
  );

  $form['reason'] = array(
    '#title' => t('Reason'),
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      'For Court Purposes' => t('For Court Purposes'),
      'For Coroner' => t('For Coroner'),
    ),
    '#disabled' => $editing,
    '#default_value' => isset($print_request['reason']) ? $print_request['reason'] : 'For Court Purposes',
  );

  $form['product'] = array(
    '#title' => t('Product'),
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      '6x4' => t('6x4'),
      '5x7' => t('5x7'),
      'CD' => t('CD'),
    ),
    '#default_value' => isset($print_request['print_product']) ? $print_request['print_product'] : '6x4',
  );

  $form['deliveryType'] = array(
    '#title' => t('Delivery Type'),
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      'Internal Dispatch' => t('Internal Dispatch'),
      'Pick Up' => t('Pick Up'),
    ),
    '#default_value' => isset($print_request['delivery_type']) ? $print_request['delivery_type'] : 'Internal Dispatch',
  );

  $form['urgency'] = array(
    '#title' => t('Urgency'),
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      'Regular' => t('Regular'),
      'Urgent' => t('Urgent'),
    ),
    '#default_value' => isset($print_request['urgency']) ? $print_request['urgency'] : 'Regular',
  );

  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('fields-container')),
  );

  $form['container']['courtUrn'] = array(
    '#title' => t('Court URN'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#disabled' => $editing,
    '#size'=> 20,
    '#default_value' => isset($print_request['court_urn']) ? $print_request['court_urn'] : NULL,
  );

  $form['container']['numberOfCopies'] = array(
    '#title' => t('Number of copies'),
    '#type' => 'numberfield',
    '#min' => 1,
    '#required' => TRUE,
    '#default_value' => isset($print_request['prints']) ? $print_request['prints'] : NULL,
  );

  $form['container']['targetDate'] = array(
    '#title' => t('Target Date'),
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d',
    '#date_label_position' => 'invisible',
    '#required' => TRUE,
    '#date_year_range' => '-10:+1',
    '#default_value' => isset($print_request['target_date']) ? $print_request['target_date'] : date('Y-m-d'),
  );

  $form['defenderName'] = array(
    '#title' => t("Defender's Name / Deceased"),
    '#type' => 'textfield',
    '#disabled' => $editing,
    '#required' => TRUE,
    '#size'=> 72,
    '#default_value' => isset($print_request['defendants_name']) ? $print_request['defendants_name'] : NULL,
  );

  $form['requestingOfficer'] = array(
    '#title' => t('Requesting Officer'),
    '#type' => 'textfield',
    '#disabled' => $editing,
    '#required' => TRUE,
    '#size'=> 72,
    '#default_value' => isset($print_request['requesting_officer']) ? $print_request['requesting_officer'] : NULL,
  );

  $form['deliveryAddress'] = array(
    '#title' => t('Delivery Address'),
    '#required' => TRUE,
    '#type' => 'textarea',
    '#default_value' => isset($print_request['delivery_address']) ? $print_request['delivery_address'] : NULL,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#value' => $editing ? t('Update') : t('Create request'),
    '#type' => 'submit',
  );

  // Check if user already has created a print request.
  $print_requests = fr_print_request_load_pending_for_user($case['case_id'], $scene['id'], fr_user_get_username());
  if(!empty($print_requests)) {
    drupal_set_message(t('You have already submitted one print request for this scene. Please wait for it to be processed before submitting another one.'), 'warning');
    $form['actions']['submit']['#disabled'] = TRUE;
  }

  return $form;
}

/**
 * Form submit callback for scene album print request form.
 */
function fr_print_request_form_submit($form, &$form_state) {
  list($case, $scene) = $form_state['build_info']['args'];

  $editing = FALSE;

  if (isset($form_state['build_info']['args'][2])) {
    $editing = TRUE;
    $print_request = $form_state['build_info']['args'][2];
  }

  $data = $form_state['values'];

  // Remove Drupal related data.
  unset($data['submit'], $data['form_build_id'], $data['form_token'], $data['form_id'], $data['op']);

  // Send id of print request if this isn't new print request.
  if ($editing) {
    $data['id'] = $print_request['id'];
  }

  $data['caseId'] = $case['case_id'];
  $data['scene'] = $scene['id'];

  try {
    $client = new PrintRequestClient();

    // Post data to service.
    if (!$editing) {
      $client->create($data);
    }
    else {
      $client->update($data);
    }

    // Response is positive.
    if (in_array($client->lastResponse->responseCode, array(200, 201))) {
      drupal_set_message($editing ? t('Print request updated.') : t('Print request submitted'));
      $form_state['redirect'] = "cases/{$case['case_id']}/scenes/{$scene['id']}/print";
    }
    // Something went wrong.
    else {
      form_set_error('', $client->lastResponse->responseMessage);
    }
  }
  catch (ServiceException $e) {
    watchdog_exception('fr_print_request', $e);
    //form_set_error('', t('Could not send your print request. Please contact system administrator.'));
    form_set_error('', $e->getMessage());
  }
}

/**
 * Form constructor for the print request approve form.
 */
function fr_print_request_approve_form($form, &$form_state, $case, $scene, $print_request) {
  return confirm_form($form,
    t('Approve print request'),
    "cases/{$case['case_id']}/scenes/{$scene['id']}/print",
    '',
    t('Approve'),
    t('Cancel')
  );
}

/**
 * Form submit callback for the print request approve form.
 */
function fr_print_request_approve_form_submit($form, &$form_state) {
  list($case, $scene, $print_request) = $form_state['build_info']['args'];

  try {
    $client = new PrintRequestClient();
    $client->approve($print_request['id']);
    $form_state['redirect'] = "cases/{$case['case_id']}/scenes/{$scene['id']}/print";
  }
  catch (ServiceException $e) {
    watchdog_exception('fr_print_request', $e);
  }
}


/**
 * Form constructor for the print request reject form.
 */
function fr_print_request_reject_form($form, &$form_state, $case, $scene, $print_request) {
  $form['reason'] = array(
    '#title' => t('Reason'),
    '#type' => 'textfield',
    '#description' => t('Provide a reason of rejecting this print request.'),
    '#required' => TRUE,
  );
  return confirm_form($form,
    t('Reject print request'),
    "cases/{$case['case_id']}/scenes/{$scene['id']}/print",
    '',
    t('Reject'),
    t('Cancel')
  );
}

/**
 * Form submit callback for the print request reject form.
 */
function fr_print_request_reject_form_submit($form, &$form_state) {
  list($case, $scene, $print_request) = $form_state['build_info']['args'];

  try {
    $client = new PrintRequestClient();
    $client->reject($print_request['id'], $form_state['values']['reason']);
    $form_state['redirect'] = "cases/{$case['case_id']}/scenes/{$scene['id']}/print";
  }
  catch (ServiceException $e) {
    watchdog_exception('fr_print_request', $e);
  }
}
