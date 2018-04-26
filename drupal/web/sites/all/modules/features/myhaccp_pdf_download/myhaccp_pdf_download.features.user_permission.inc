<?php
/**
 * @file
 * myhaccp_pdf_download.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function myhaccp_pdf_download_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access PDF version'.
  $permissions['access PDF version'] = array(
    'name' => 'access PDF version',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'print_pdf',
  );

  return $permissions;
}
