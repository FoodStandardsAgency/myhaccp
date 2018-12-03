<?php
/**
 * @file
 * myhaccp_bean_type_notice.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_bean_type_notice_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer backup and migrate'.
  $permissions['administer backup and migrate'] = array(
    'name' => 'administer backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'create any notice bean'.
  $permissions['create any notice bean'] = array(
    'name' => 'create any notice bean',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'delete any notice bean'.
  $permissions['delete any notice bean'] = array(
    'name' => 'delete any notice bean',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'edit any notice bean'.
  $permissions['edit any notice bean'] = array(
    'name' => 'edit any notice bean',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'view any notice bean'.
  $permissions['view any notice bean'] = array(
    'name' => 'view any notice bean',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'bean',
  );

  return $permissions;
}
