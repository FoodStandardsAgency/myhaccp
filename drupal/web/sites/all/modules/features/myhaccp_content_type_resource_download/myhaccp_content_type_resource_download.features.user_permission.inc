<?php
/**
 * @file
 * myhaccp_content_type_resource_download.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_content_type_resource_download_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create resource_download content'.
  $permissions['create resource_download content'] = array(
    'name' => 'create resource_download content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any resource_download content'.
  $permissions['delete any resource_download content'] = array(
    'name' => 'delete any resource_download content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own resource_download content'.
  $permissions['delete own resource_download content'] = array(
    'name' => 'delete own resource_download content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any resource_download content'.
  $permissions['edit any resource_download content'] = array(
    'name' => 'edit any resource_download content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own resource_download content'.
  $permissions['edit own resource_download content'] = array(
    'name' => 'edit own resource_download content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
