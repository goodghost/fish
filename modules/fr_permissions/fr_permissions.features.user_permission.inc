<?php
/**
 * @file
 * fr_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function fr_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(),
    'module' => 'contextual',
  );

  // Exported permission: 'access navbar'.
  $permissions['access navbar'] = array(
    'name' => 'access navbar',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'navbar',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'manager' => 'manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer advanced pane settings'.
  $permissions['administer advanced pane settings'] = array(
    'name' => 'administer advanced pane settings',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'og',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer page manager'.
  $permissions['administer page manager'] = array(
    'name' => 'administer page manager',
    'roles' => array(),
    'module' => 'page_manager',
  );

  // Exported permission: 'administer pane access'.
  $permissions['administer pane access'] = array(
    'name' => 'administer pane access',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'administer panelizer'.
  $permissions['administer panelizer'] = array(
    'name' => 'administer panelizer',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node dashboard content'.
  $permissions['administer panelizer node dashboard content'] = array(
    'name' => 'administer panelizer node dashboard content',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node dashboard context'.
  $permissions['administer panelizer node dashboard context'] = array(
    'name' => 'administer panelizer node dashboard context',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node dashboard defaults'.
  $permissions['administer panelizer node dashboard defaults'] = array(
    'name' => 'administer panelizer node dashboard defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node dashboard layout'.
  $permissions['administer panelizer node dashboard layout'] = array(
    'name' => 'administer panelizer node dashboard layout',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node dashboard overview'.
  $permissions['administer panelizer node dashboard overview'] = array(
    'name' => 'administer panelizer node dashboard overview',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node dashboard settings'.
  $permissions['administer panelizer node dashboard settings'] = array(
    'name' => 'administer panelizer node dashboard settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panels layouts'.
  $permissions['administer panels layouts'] = array(
    'name' => 'administer panels layouts',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'administer panels styles'.
  $permissions['administer panels styles'] = array(
    'name' => 'administer panels styles',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'approve print requests'.
  $permissions['approve print requests'] = array(
    'name' => 'approve print requests',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'fr_print_request',
  );

  // Exported permission: 'assign work to myself'.
  $permissions['assign work to myself'] = array(
    'name' => 'assign work to myself',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'manager' => 'manager',
    ),
    'module' => 'fr_work_assignment',
  );

  // Exported permission: 'assign work to other users'.
  $permissions['assign work to other users'] = array(
    'name' => 'assign work to other users',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'fr_work_assignment',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'change layouts in place editing'.
  $permissions['change layouts in place editing'] = array(
    'name' => 'change layouts in place editing',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'create dashboard content'.
  $permissions['create dashboard content'] = array(
    'name' => 'create dashboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create group content'.
  $permissions['create group content'] = array(
    'name' => 'create group content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create report content'.
  $permissions['create report content'] = array(
    'name' => 'create report content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create wallboard content'.
  $permissions['create wallboard content'] = array(
    'name' => 'create wallboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any dashboard content'.
  $permissions['delete any dashboard content'] = array(
    'name' => 'delete any dashboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any group content'.
  $permissions['delete any group content'] = array(
    'name' => 'delete any group content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any report content'.
  $permissions['delete any report content'] = array(
    'name' => 'delete any report content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any wallboard content'.
  $permissions['delete any wallboard content'] = array(
    'name' => 'delete any wallboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own dashboard content'.
  $permissions['delete own dashboard content'] = array(
    'name' => 'delete own dashboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own group content'.
  $permissions['delete own group content'] = array(
    'name' => 'delete own group content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own report content'.
  $permissions['delete own report content'] = array(
    'name' => 'delete own report content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own wallboard content'.
  $permissions['delete own wallboard content'] = array(
    'name' => 'delete own wallboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any dashboard content'.
  $permissions['edit any dashboard content'] = array(
    'name' => 'edit any dashboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any group content'.
  $permissions['edit any group content'] = array(
    'name' => 'edit any group content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any print request'.
  $permissions['edit any print request'] = array(
    'name' => 'edit any print request',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'fr_print_request',
  );

  // Exported permission: 'edit any report content'.
  $permissions['edit any report content'] = array(
    'name' => 'edit any report content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any wallboard content'.
  $permissions['edit any wallboard content'] = array(
    'name' => 'edit any wallboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own dashboard content'.
  $permissions['edit own dashboard content'] = array(
    'name' => 'edit own dashboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own group content'.
  $permissions['edit own group content'] = array(
    'name' => 'edit own group content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own report content'.
  $permissions['edit own report content'] = array(
    'name' => 'edit own report content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own wallboard content'.
  $permissions['edit own wallboard content'] = array(
    'name' => 'edit own wallboard content',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'node',
  );

  // Exported permission: 'reject print requests'.
  $permissions['reject print requests'] = array(
    'name' => 'reject print requests',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'fr_print_request',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'use ipe with page manager'.
  $permissions['use ipe with page manager'] = array(
    'name' => 'use ipe with page manager',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'use page manager'.
  $permissions['use page manager'] = array(
    'name' => 'use page manager',
    'roles' => array(),
    'module' => 'page_manager',
  );

  // Exported permission: 'use panels caching features'.
  $permissions['use panels caching features'] = array(
    'name' => 'use panels caching features',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'use panels dashboard'.
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'use panels in place editing'.
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(
      'builder' => 'builder',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels locks'.
  $permissions['use panels locks'] = array(
    'name' => 'use panels locks',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'view pane admin links'.
  $permissions['view pane admin links'] = array(
    'name' => 'view pane admin links',
    'roles' => array(),
    'module' => 'panels',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'view scene restricted images'.
  $permissions['view scene restricted images'] = array(
    'name' => 'view scene restricted images',
    'roles' => array(),
    'module' => 'fr_case',
  );

  return $permissions;
}
