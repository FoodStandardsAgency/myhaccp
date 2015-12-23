<?php
/**
 * @file
 * myhaccp_content_type_resource_download.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function myhaccp_content_type_resource_download_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|resource_download|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'resource_download';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title_field' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['node|resource_download|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function myhaccp_content_type_resource_download_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resource_download|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resource_download';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title_field',
        1 => 'field_description',
        2 => 'field_category',
        3 => 'field_file',
      ),
    ),
    'fields' => array(
      'title_field' => 'ds_content',
      'field_description' => 'ds_content',
      'field_category' => 'ds_content',
      'field_file' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'hide_page_title' => '1',
    'page_option_title' => '',
  );
  $export['node|resource_download|full'] = $ds_layout;

  return $export;
}
