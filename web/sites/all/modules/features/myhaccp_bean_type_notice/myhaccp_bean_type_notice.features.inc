<?php
/**
 * @file
 * myhaccp_bean_type_notice.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_bean_type_notice_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "bean_admin_ui" && $api == "bean") {
    return array("version" => "5");
  }
}
