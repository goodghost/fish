<?php
/**
 * @file
 * fr_permissions.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function fr_permissions_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:group:add user'
  $permissions['node:group:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:administer group'
  $permissions['node:group:administer group'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:approve and deny subscription'
  $permissions['node:group:approve and deny subscription'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create dashboard content'
  $permissions['node:group:create dashboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create report content'
  $permissions['node:group:create report content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create wallboard content'
  $permissions['node:group:create wallboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any dashboard content'
  $permissions['node:group:delete any dashboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any report content'
  $permissions['node:group:delete any report content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any wallboard content'
  $permissions['node:group:delete any wallboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own dashboard content'
  $permissions['node:group:delete own dashboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own report content'
  $permissions['node:group:delete own report content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own wallboard content'
  $permissions['node:group:delete own wallboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:manage members'
  $permissions['node:group:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:manage permissions'
  $permissions['node:group:manage permissions'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:manage roles'
  $permissions['node:group:manage roles'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:subscribe'
  $permissions['node:group:subscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:subscribe without approval'
  $permissions['node:group:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:unsubscribe'
  $permissions['node:group:unsubscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any dashboard content'
  $permissions['node:group:update any dashboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any report content'
  $permissions['node:group:update any report content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any wallboard content'
  $permissions['node:group:update any wallboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update group'
  $permissions['node:group:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own dashboard content'
  $permissions['node:group:update own dashboard content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update own report content'
  $permissions['node:group:update own report content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update own wallboard content'
  $permissions['node:group:update own wallboard content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
