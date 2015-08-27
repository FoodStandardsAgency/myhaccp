<?php
/**
 * @file
 * myhaccp_user_profiles.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function myhaccp_user_profiles_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : true, "use_page" : true },
    "rdf_mapping" : []
  }');
  return $items;
}
