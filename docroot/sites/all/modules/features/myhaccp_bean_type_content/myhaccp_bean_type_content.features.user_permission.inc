<?php
/**
 * @file
 * myhaccp_bean_type_content.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_bean_type_content_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access bean overview'.
  $permissions['access bean overview'] = array(
    'name' => 'access bean overview',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'administer bean settings'.
  $permissions['administer bean settings'] = array(
    'name' => 'administer bean settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'administer bean types'.
  $permissions['administer bean types'] = array(
    'name' => 'administer bean types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'administer beans'.
  $permissions['administer beans'] = array(
    'name' => 'administer beans',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'create any content bean'.
  $permissions['create any content bean'] = array(
    'name' => 'create any content bean',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'delete any content bean'.
  $permissions['delete any content bean'] = array(
    'name' => 'delete any content bean',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'edit any content bean'.
  $permissions['edit any content bean'] = array(
    'name' => 'edit any content bean',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'edit bean view mode'.
  $permissions['edit bean view mode'] = array(
    'name' => 'edit bean view mode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'view any content bean'.
  $permissions['view any content bean'] = array(
    'name' => 'view any content bean',
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

  // Exported permission: 'view bean page'.
  $permissions['view bean page'] = array(
    'name' => 'view bean page',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: 'view bean revisions'.
  $permissions['view bean revisions'] = array(
    'name' => 'view bean revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'bean',
  );

  return $permissions;
}
