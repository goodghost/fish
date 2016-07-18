<?php
/**
 * @file
 * fr_user.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function fr_user_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: builder.
  $roles['builder'] = array(
    'name' => 'builder',
    'weight' => 3,
  );

  // Exported role: manager.
  $roles['manager'] = array(
    'name' => 'manager',
    'weight' => 4,
  );

  return $roles;
}
