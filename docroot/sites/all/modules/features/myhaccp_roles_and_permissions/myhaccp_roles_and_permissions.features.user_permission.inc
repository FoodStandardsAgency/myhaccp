<?php
/**
 * @file
 * myhaccp_roles_and_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_roles_and_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access backup and migrate'.
  $permissions['access backup and migrate'] = array(
    'name' => 'access backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access site map'.
  $permissions['access site map'] = array(
    'name' => 'access site map',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'site_map',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'add terms in file_category'.
  $permissions['add terms in file_category'] = array(
    'name' => 'add terms in file_category',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'taxonomy_access_fix',
  );

  // Exported permission: 'admin node search exlusions'.
  $permissions['admin node search exlusions'] = array(
    'name' => 'admin node search exlusions',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'assign all roles'.
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign help and guidance manager role'.
  $permissions['assign help and guidance manager role'] = array(
    'name' => 'assign help and guidance manager role',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign site manager role'.
  $permissions['assign site manager role'] = array(
    'name' => 'assign site manager role',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign translator role'.
  $permissions['assign translator role'] = array(
    'name' => 'assign translator role',
    'roles' => array(),
    'module' => 'role_delegation',
  );

  // Exported permission: 'bypass rh_node'.
  $permissions['bypass rh_node'] = array(
    'name' => 'bypass rh_node',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'rabbit_hole',
  );

  // Exported permission: 'clone any myhaccp study'.
  $permissions['clone any myhaccp study'] = array(
    'name' => 'clone any myhaccp study',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'clone own myhaccp study'.
  $permissions['clone own myhaccp study'] = array(
    'name' => 'clone own myhaccp study',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'close bean'.
  $permissions['close bean'] = array(
    'name' => 'close bean',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
      'translator' => 'translator',
    ),
    'module' => 'close_bean',
  );

  // Exported permission: 'create files'.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'create myhaccp study'.
  $permissions['create myhaccp study'] = array(
    'name' => 'create myhaccp study',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any audio files'.
  $permissions['delete any audio files'] = array(
    'name' => 'delete any audio files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any document files'.
  $permissions['delete any document files'] = array(
    'name' => 'delete any document files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any image files'.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any myhaccp study'.
  $permissions['delete any myhaccp study'] = array(
    'name' => 'delete any myhaccp study',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'delete any video files'.
  $permissions['delete any video files'] = array(
    'name' => 'delete any video files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own audio files'.
  $permissions['delete own audio files'] = array(
    'name' => 'delete own audio files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own document files'.
  $permissions['delete own document files'] = array(
    'name' => 'delete own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own image files'.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own myhaccp study'.
  $permissions['delete own myhaccp study'] = array(
    'name' => 'delete own myhaccp study',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'delete own video files'.
  $permissions['delete own video files'] = array(
    'name' => 'delete own video files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in file_category'.
  $permissions['delete terms in file_category'] = array(
    'name' => 'delete terms in file_category',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'download any audio files'.
  $permissions['download any audio files'] = array(
    'name' => 'download any audio files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any document files'.
  $permissions['download any document files'] = array(
    'name' => 'download any document files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any image files'.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any video files'.
  $permissions['download any video files'] = array(
    'name' => 'download any video files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own audio files'.
  $permissions['download own audio files'] = array(
    'name' => 'download own audio files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own document files'.
  $permissions['download own document files'] = array(
    'name' => 'download own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own image files'.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own video files'.
  $permissions['download own video files'] = array(
    'name' => 'download own video files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any audio files'.
  $permissions['edit any audio files'] = array(
    'name' => 'edit any audio files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any document files'.
  $permissions['edit any document files'] = array(
    'name' => 'edit any document files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any image files'.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any myhaccp study'.
  $permissions['edit any myhaccp study'] = array(
    'name' => 'edit any myhaccp study',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'edit any video files'.
  $permissions['edit any video files'] = array(
    'name' => 'edit any video files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own audio files'.
  $permissions['edit own audio files'] = array(
    'name' => 'edit own audio files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own document files'.
  $permissions['edit own document files'] = array(
    'name' => 'edit own document files',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own image files'.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own myhaccp study'.
  $permissions['edit own myhaccp study'] = array(
    'name' => 'edit own myhaccp study',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'edit own video files'.
  $permissions['edit own video files'] = array(
    'name' => 'edit own video files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit terms in file_category'.
  $permissions['edit terms in file_category'] = array(
    'name' => 'edit terms in file_category',
    'roles' => array(
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit webform components'.
  $permissions['edit webform components'] = array(
    'name' => 'edit webform components',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'list any myhaccp study'.
  $permissions['list any myhaccp study'] = array(
    'name' => 'list any myhaccp study',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'list own myhaccp study'.
  $permissions['list own myhaccp study'] = array(
    'name' => 'list own myhaccp study',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search all content'.
  $permissions['search all content'] = array(
    'name' => 'search all content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search all excluded entities'.
  $permissions['search all excluded entities'] = array(
    'name' => 'search all excluded entities',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: 'search guidance content'.
  $permissions['search guidance content'] = array(
    'name' => 'search guidance content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search page content'.
  $permissions['search page content'] = array(
    'name' => 'search page content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search resource_download content'.
  $permissions['search resource_download content'] = array(
    'name' => 'search resource_download content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search resource_link content'.
  $permissions['search resource_link content'] = array(
    'name' => 'search resource_link content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search webform content'.
  $permissions['search webform content'] = array(
    'name' => 'search webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view any myhaccp study'.
  $permissions['view any myhaccp study'] = array(
    'name' => 'view any myhaccp study',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'view files'.
  $permissions['view files'] = array(
    'name' => 'view files',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own files'.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own myhaccp study'.
  $permissions['view own myhaccp study'] = array(
    'name' => 'view own myhaccp study',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'myhaccp',
  );

  // Exported permission: 'view own private files'.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view private files'.
  $permissions['view private files'] = array(
    'name' => 'view private files',
    'roles' => array(
      'administrator' => 'administrator',
      'site manager' => 'site manager',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
      'site manager' => 'site manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
      'help and guidance manager' => 'help and guidance manager',
    ),
    'module' => 'system',
  );

  return $permissions;
}
