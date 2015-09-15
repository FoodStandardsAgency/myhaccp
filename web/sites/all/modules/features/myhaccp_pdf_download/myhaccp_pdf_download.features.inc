<?php
/**
 * @file
 * myhaccp_pdf_download.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_pdf_download_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
