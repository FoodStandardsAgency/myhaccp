<?php
/**
 * @file
 * myhaccp_content_type_resource_link.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_content_type_resource_link_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create resource_link content'.
  $permissions['create resource_link content'] = array(
    'name' => 'create resource_link content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any resource_link content'.
  $permissions['delete any resource_link content'] = array(
    'name' => 'delete any resource_link content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own resource_link content'.
  $permissions['delete own resource_link content'] = array(
    'name' => 'delete own resource_link content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any resource_link content'.
  $permissions['edit any resource_link content'] = array(
    'name' => 'edit any resource_link content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own resource_link content'.
  $permissions['edit own resource_link content'] = array(
    'name' => 'edit own resource_link content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
