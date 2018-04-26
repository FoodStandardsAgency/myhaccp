<?php
/**
 * @file
 * myhaccp_roles_and_permissions.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_roles_and_permissions_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "password_policy" && $api == "default_password_policy") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
