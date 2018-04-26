<?php
/**
 * @file
 * myhaccp_content_type_guidance.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_content_type_guidance_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create guidance content'.
  $permissions['create guidance content'] = array(
    'name' => 'create guidance content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any guidance content'.
  $permissions['delete any guidance content'] = array(
    'name' => 'delete any guidance content',
    'roles' => array(
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own guidance content'.
  $permissions['delete own guidance content'] = array(
    'name' => 'delete own guidance content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any guidance content'.
  $permissions['edit any guidance content'] = array(
    'name' => 'edit any guidance content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own guidance content'.
  $permissions['edit own guidance content'] = array(
    'name' => 'edit own guidance content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
