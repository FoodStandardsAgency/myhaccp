<?php
/**
 * @file
 * myhaccp_roles_and_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function myhaccp_roles_and_permissions_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: help and guidance manager.
  $roles['help and guidance manager'] = array(
    'name' => 'help and guidance manager',
    'weight' => 3,
  );

  // Exported role: site manager.
  $roles['site manager'] = array(
    'name' => 'site manager',
    'weight' => 4,
  );

  return $roles;
}
