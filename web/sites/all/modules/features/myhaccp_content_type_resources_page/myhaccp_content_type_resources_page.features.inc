<?php
/**
 * @file
 * myhaccp_content_type_resources_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_content_type_resources_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function myhaccp_content_type_resources_page_node_info() {
  $items = array(
    'resources_page' => array(
      'name' => t('Resources Page'),
      'base' => 'node_content',
      'description' => t('A page to be used for displaying resources'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
