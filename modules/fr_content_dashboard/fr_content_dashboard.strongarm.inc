<?php
/**
 * @file
 * fr_content_dashboard.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function fr_content_dashboard_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_dashboard';
  $strongarm->value = '0';
  $export['ant_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_dashboard';
  $strongarm->value = '';
  $export['ant_pattern_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_dashboard';
  $strongarm->value = 0;
  $export['ant_php_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_dashboard';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_dashboard';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_dashboard';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__dashboard';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_dashboard';
  $strongarm->value = '0';
  $export['language_content_type_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_dashboard';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_dashboard';
  $strongarm->value = '1';
  $export['node_preview_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_dashboard';
  $strongarm->value = 0;
  $export['node_submitted_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_dashboard';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 1,
      ),
      'default' => array(
        'status' => 0,
        'default' => 1,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_dashboard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:dashboard_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:24:"panelizer_node:dashboard";s:23:"allowed_layout_settings";a:9:{s:8:"flexible";b:0;s:14:"twocol_stacked";b:1;s:13:"twocol_bricks";b:1;s:6:"twocol";b:1;s:25:"threecol_33_34_33_stacked";b:1;s:17:"threecol_33_34_33";b:1;s:25:"threecol_25_50_25_stacked";b:1;s:17:"threecol_25_50_25";b:1;s:6:"onecol";b:1;}s:10:"form_state";N;}';
  $export['panelizer_node:dashboard_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:dashboard_allowed_layouts_default';
  $strongarm->value = 0;
  $export['panelizer_node:dashboard_allowed_layouts_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:dashboard_allowed_types';
  $strongarm->value = array(
    'vocabulary_terms-vocabulary_terms' => 0,
    'user_links-user_links' => 0,
    'user_picture-user_picture' => 0,
    'user_profile-user_profile' => 0,
    'user_signature-user_signature' => 0,
    'term_description-term_description' => 0,
    'term_list-term_list' => 0,
    'term_name-term_name' => 0,
    'page_actions-page_actions' => 0,
    'page_breadcrumb-page_breadcrumb' => 0,
    'page_feed_icons-page_feed_icons' => 0,
    'page_help-page_help' => 0,
    'page_logo-page_logo' => 0,
    'page_messages-page_messages' => 0,
    'page_primary_links-page_primary_links' => 0,
    'page_secondary_links-page_secondary_links' => 0,
    'page_site_name-page_site_name' => 0,
    'page_slogan-page_slogan' => 0,
    'page_tabs-page_tabs' => 0,
    'page_title-page_title' => 0,
    'node_form_author-node_form_author' => 0,
    'node_form_buttons-node_form_buttons' => 0,
    'node_form_language-node_form_language' => 0,
    'node_form_log-node_form_log' => 0,
    'node_form_menu-node_form_menu' => 0,
    'node_form_publishing-node_form_publishing' => 0,
    'node_form_title-node_form_title' => 0,
    'node_attachments-node_attachments' => 0,
    'node_author-node_author' => 0,
    'node_body-node_body' => 0,
    'node_content-node_content' => 0,
    'node_created-node_created' => 0,
    'node_links-node_links' => 0,
    'node_terms-node_terms' => 0,
    'node_title-node_title' => 0,
    'node_type_desc-node_type_desc' => 0,
    'node_updated-node_updated' => 0,
    'form-form' => 0,
    'comment_links-comment_links' => 0,
    'file_content-file_content' => 0,
    'file_display-file_display' => 0,
    'membership_links-membership_links' => 0,
    'panelizer_form_default-panelizer_form_default' => 0,
    'token-node:source' => 0,
    'token-node:log' => 0,
    'token-node:content-type' => 0,
    'token-node:diff' => 0,
    'token-node:diff-markdown' => 0,
    'token-node:menu-link' => 0,
    'token-node:nid' => 0,
    'token-node:vid' => 0,
    'token-node:title' => 0,
    'token-node:body' => 0,
    'token-node:summary' => 0,
    'token-node:language' => 0,
    'token-node:url' => 0,
    'token-node:edit-url' => 0,
    'token-node:created' => 0,
    'token-node:changed' => 0,
    'token-node:author' => 0,
    'token-node:uuid' => 0,
    'token-node:vuuid' => 0,
    'token-node:original' => 0,
    'token-node:is-new' => 0,
    'token-node:status' => 0,
    'token-node:promote' => 0,
    'token-node:sticky' => 0,
    'token-node:revision' => 0,
    'token-node:field-description' => 0,
    'token-node:og-group-ref' => 0,
    'token-node:og-membership' => 0,
    'token-node:og-membership--1' => 0,
    'token-node:og-membership--2' => 0,
    'token-node:og-membership--3' => 0,
    'token-node:og-group-ref--og-membership' => 0,
    'token-node:og-group-ref--og-membership--1' => 0,
    'token-node:og-group-ref--og-membership--2' => 0,
    'token-node:og-group-ref--og-membership--3' => 0,
    'token-node:group-access' => 0,
    'token-node:group-group' => 0,
    'token-node:members' => 0,
    'token-node:members--1' => 0,
    'token-node:members--2' => 0,
    'token-node:members--3' => 0,
    'token-node:field_description' => 0,
    'token-node:og_group_ref' => 0,
    'token-node:group_access' => 0,
    'token-node:group_group' => 0,
    'token-node:field_dataset' => 0,
    'token-content-type:name' => 0,
    'token-content-type:machine-name' => 0,
    'token-content-type:description' => 0,
    'token-content-type:node-count' => 0,
    'token-content-type:edit-url' => 0,
    'token-term:edit-url' => 0,
    'token-term:parents' => 0,
    'token-term:root' => 0,
    'token-term:tid' => 0,
    'token-term:name' => 0,
    'token-term:description' => 0,
    'token-term:node-count' => 0,
    'token-term:url' => 0,
    'token-term:vocabulary' => 0,
    'token-term:parent' => 0,
    'token-term:uuid' => 0,
    'token-term:original' => 0,
    'token-term:weight' => 0,
    'token-term:parents-all' => 0,
    'token-vocabulary:machine-name' => 0,
    'token-vocabulary:edit-url' => 0,
    'token-vocabulary:vid' => 0,
    'token-vocabulary:name' => 0,
    'token-vocabulary:description' => 0,
    'token-vocabulary:node-count' => 0,
    'token-vocabulary:term-count' => 0,
    'token-vocabulary:original' => 0,
    'token-file:basename' => 0,
    'token-file:extension' => 0,
    'token-file:size-raw' => 0,
    'token-file:type' => 0,
    'token-file:download-url' => 0,
    'token-file:fid' => 0,
    'token-file:name' => 0,
    'token-file:path' => 0,
    'token-file:mime' => 0,
    'token-file:size' => 0,
    'token-file:url' => 0,
    'token-file:timestamp' => 0,
    'token-file:owner' => 0,
    'token-file:uuid' => 0,
    'token-file:original' => 0,
    'token-file:field-file-image-alt-text' => 0,
    'token-file:field-file-image-title-text' => 0,
    'token-file:field_file_image_alt_text' => 0,
    'token-file:field_file_image_title_text' => 0,
    'token-user:cancel-url' => 0,
    'token-user:one-time-login-url' => 0,
    'token-user:picture' => 0,
    'token-user:roles' => 0,
    'token-user:uid' => 0,
    'token-user:name' => 0,
    'token-user:mail' => 0,
    'token-user:url' => 0,
    'token-user:edit-url' => 0,
    'token-user:last-login' => 0,
    'token-user:created' => 0,
    'token-user:uuid' => 0,
    'token-user:original' => 0,
    'token-user:last-access' => 0,
    'token-user:status' => 0,
    'token-user:theme' => 0,
    'token-user:og-user-node' => 0,
    'token-user:og-membership' => 0,
    'token-user:og-membership--1' => 0,
    'token-user:og-membership--2' => 0,
    'token-user:og-membership--3' => 0,
    'token-user:og-user-node--og-membership' => 0,
    'token-user:og-user-node--og-membership--1' => 0,
    'token-user:og-user-node--og-membership--2' => 0,
    'token-user:og-user-node--og-membership--3' => 0,
    'token-user:og_user_node' => 0,
    'token-current-user:ip-address' => 0,
    'token-menu-link:mlid' => 0,
    'token-menu-link:title' => 0,
    'token-menu-link:url' => 0,
    'token-menu-link:parent' => 0,
    'token-menu-link:parents' => 0,
    'token-menu-link:root' => 0,
    'token-menu-link:menu' => 0,
    'token-menu-link:edit-url' => 0,
    'token-current-page:title' => 0,
    'token-current-page:url' => 0,
    'token-current-page:page-number' => 0,
    'token-current-page:query' => 0,
    'token-url:path' => 0,
    'token-url:relative' => 0,
    'token-url:absolute' => 0,
    'token-url:brief' => 0,
    'token-url:unaliased' => 0,
    'token-url:args' => 0,
    'token-array:first' => 0,
    'token-array:last' => 0,
    'token-array:count' => 0,
    'token-array:reversed' => 0,
    'token-array:keys' => 0,
    'token-array:join' => 0,
    'token-array:value' => 0,
    'token-random:number' => 0,
    'token-random:hash' => 0,
    'token-address-field:country' => 0,
    'token-address-field:country-code' => 0,
    'token-address-field:administrative-area' => 0,
    'token-address-field:administrative-area-raw' => 0,
    'token-address-field:locality' => 0,
    'token-address-field:postal-code' => 0,
    'token-address-field:thoroughfare' => 0,
    'token-address-field:premise' => 0,
    'token-address-field:sub_premise' => 0,
    'token-address-field:organisation' => 0,
    'token-address-field:name-line' => 0,
    'token-address-field:first-name' => 0,
    'token-address-field:last-name' => 0,
    'token-address-field:format-mailchimp' => 0,
    'token-file-type:name' => 0,
    'token-file-type:machine-name' => 0,
    'token-file-type:count' => 0,
    'token-file-type:edit-url' => 0,
    'token-menu:name' => 0,
    'token-menu:machine-name' => 0,
    'token-menu:description' => 0,
    'token-menu:menu-link-count' => 0,
    'token-menu:edit-url' => 0,
    'token-site:name' => 0,
    'token-site:slogan' => 0,
    'token-site:mail' => 0,
    'token-site:url' => 0,
    'token-site:url-brief' => 0,
    'token-site:login-url' => 0,
    'token-site:current-user' => 0,
    'token-site:current-date' => 0,
    'token-site:current-page' => 0,
    'token-date:short' => 0,
    'token-date:medium' => 0,
    'token-date:long' => 0,
    'token-date:custom' => 0,
    'token-date:since' => 0,
    'token-date:raw' => 0,
    'token-field_collection_item:uuid' => 0,
    'token-field_collection_item:item-id' => 0,
    'token-field_collection_item:revision-id' => 0,
    'token-field_collection_item:archived' => 0,
    'token-field_collection_item:url' => 0,
    'token-view:name' => 0,
    'token-view:description' => 0,
    'token-view:machine-name' => 0,
    'token-view:title' => 0,
    'token-view:url' => 0,
    'token-og_membership_type:id' => 0,
    'token-og_membership_type:description' => 0,
    'token-og_membership_type:status' => 0,
    'token-og_membership_type:module' => 0,
    'token-og_membership_type:language' => 0,
    'token-og_membership:id' => 0,
    'token-og_membership:type' => 0,
    'token-og_membership:entity-type' => 0,
    'token-og_membership:group-type' => 0,
    'token-og_membership:state' => 0,
    'token-og_membership:created' => 0,
    'token-og_membership:field-name' => 0,
    'token-og_membership:language' => 0,
    'token-og_membership:og-membership-request' => 0,
    'token-og_membership:og_membership_request' => 0,
    'token-list<field_collection_item>:0' => 0,
    'token-list<field_collection_item>:1' => 0,
    'token-list<field_collection_item>:2' => 0,
    'token-list<field_collection_item>:3' => 0,
    'token-list<node>:0' => 0,
    'token-list<node>:1' => 0,
    'token-list<node>:2' => 0,
    'token-list<node>:3' => 0,
    'token-list<og_membership_type>:0' => 0,
    'token-list<og_membership_type>:1' => 0,
    'token-list<og_membership_type>:2' => 0,
    'token-list<og_membership_type>:3' => 0,
    'token-list<og_membership>:0' => 0,
    'token-list<og_membership>:1' => 0,
    'token-list<og_membership>:2' => 0,
    'token-list<og_membership>:3' => 0,
    'token-list<file>:0' => 0,
    'token-list<file>:1' => 0,
    'token-list<file>:2' => 0,
    'token-list<file>:3' => 0,
    'token-list<term>:0' => 0,
    'token-list<term>:1' => 0,
    'token-list<term>:2' => 0,
    'token-list<term>:3' => 0,
    'token-list<vocabulary>:0' => 0,
    'token-list<vocabulary>:1' => 0,
    'token-list<vocabulary>:2' => 0,
    'token-list<vocabulary>:3' => 0,
    'token-list<user>:0' => 0,
    'token-list<user>:1' => 0,
    'token-list<user>:2' => 0,
    'token-list<user>:3' => 0,
    'token-list<date>:0' => 0,
    'token-list<date>:1' => 0,
    'token-list<date>:2' => 0,
    'token-list<date>:3' => 0,
    'node-report' => 0,
    'node-existing_node' => 'node-existing_node',
    'node-dashboard' => 0,
    'node-group' => 0,
    'entity_form_field-node:field_description' => 0,
    'entity_form_field-node:og_group_ref' => 0,
    'entity_form_field-node:group_access' => 0,
    'entity_form_field-node:group_group' => 0,
    'entity_form_field-node:field_dataset' => 0,
    'entity_form_field-og_membership:og_membership_request' => 0,
    'entity_form_field-file:field_file_image_alt_text' => 0,
    'entity_form_field-file:field_file_image_title_text' => 0,
    'entity_form_field-user:og_user_node' => 0,
    'entity_field-node:field_description' => 0,
    'entity_field-node:og_group_ref' => 0,
    'entity_field-node:group_access' => 0,
    'entity_field-node:group_group' => 0,
    'entity_field-node:field_dataset' => 0,
    'entity_field-og_membership:og_membership_request' => 0,
    'entity_field-file:field_file_image_alt_text' => 0,
    'entity_field-file:field_file_image_title_text' => 0,
    'entity_field-user:og_user_node' => 0,
    'entity_field_extra-node:group_content' => 0,
    'entity_field_extra-file:file' => 0,
    'entity_field_extra-user:summary' => 0,
    'custom-custom' => 0,
    'block-diff-inline' => 0,
    'block-locale-language' => 0,
    'block-menu-devel' => 0,
    'block-node-syndicate' => 0,
    'block-node-recent' => 0,
    'block-shortcut-shortcuts' => 0,
    'block-system-powered-by' => 0,
    'block-system-help' => 0,
    'block-system-navigation' => 0,
    'block-system-management' => 0,
    'block-system-user-menu' => 0,
    'block-system-main-menu' => 0,
    'block-user-login' => 0,
    'block-user-new' => 0,
    'block-user-online' => 0,
    'block-views-og_members-block_1' => 0,
    'block-devel-execute_php' => 0,
    'block-devel-switch_user' => 0,
    'entity_view-field_collection_item' => 0,
    'entity_view-node' => 0,
    'entity_view-og_membership_type' => 0,
    'entity_view-og_membership' => 0,
    'entity_view-file' => 0,
    'entity_view-taxonomy_term' => 0,
    'entity_view-user' => 0,
  );
  $export['panelizer_node:dashboard_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:dashboard_allowed_types_default';
  $strongarm->value = 0;
  $export['panelizer_node:dashboard_allowed_types_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:dashboard_default';
  $strongarm->value = array(
    'node' => 'node',
    'token' => 0,
    'entity_form_field' => 0,
    'entity_field' => 0,
    'entity_field_extra' => 0,
    'custom' => 0,
    'block' => 0,
    'entity_view' => 0,
    'other' => 0,
  );
  $export['panelizer_node:dashboard_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_dashboard';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_dashboard'] = $strongarm;

  return $export;
}
