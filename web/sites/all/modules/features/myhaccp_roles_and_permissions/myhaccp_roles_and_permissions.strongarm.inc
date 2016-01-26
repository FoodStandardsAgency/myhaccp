<?php
/**
 * @file
 * myhaccp_roles_and_permissions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function myhaccp_roles_and_permissions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_register';
  $strongarm->value = '1';
  $export['user_register'] = $strongarm;

  return $export;
}
