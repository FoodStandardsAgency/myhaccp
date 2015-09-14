<?php
/**
 * @file
 * myhaccp_content_type_resource_download.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_content_type_resource_download_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function myhaccp_content_type_resource_download_node_info() {
  $items = array(
    'resource_download' => array(
      'name' => t('Resource (download)'),
      'base' => 'node_content',
      'description' => t('A resource which is a file download stored locally.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
