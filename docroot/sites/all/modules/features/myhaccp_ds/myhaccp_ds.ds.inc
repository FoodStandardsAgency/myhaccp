<?php
/**
 * @file
 * myhaccp_ds.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function myhaccp_ds_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'full_without_title';
  $ds_view_mode->label = 'Full without title';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['full_without_title'] = $ds_view_mode;

  return $export;
}
