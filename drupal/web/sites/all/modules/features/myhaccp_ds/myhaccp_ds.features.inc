<?php
/**
 * @file
 * myhaccp_ds.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_ds_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}
