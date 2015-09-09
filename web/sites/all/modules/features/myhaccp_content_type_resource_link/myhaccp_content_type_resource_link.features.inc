<?php
/**
 * @file
 * myhaccp_content_type_resource_link.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function myhaccp_content_type_resource_link_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function myhaccp_content_type_resource_link_node_info() {
  $items = array(
    'resource_link' => array(
      'name' => t('Resource (link)'),
      'base' => 'node_content',
      'description' => t('A resource which is an external link.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
