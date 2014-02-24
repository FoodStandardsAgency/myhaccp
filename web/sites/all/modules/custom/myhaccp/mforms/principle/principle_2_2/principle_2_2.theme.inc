<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_2_2().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_2_2(&$variables) {
  // @todo pull in data on hazards e.g Step No. / hazard name

  $stage = 'principle_2_2';
  $values = $variables['data'][$stage];


  //$stages = new Stages();
  //$stage = $stages->getStage(__FUNCTION__);

  //$store = MformsDatabaseStore::getInstance('myhaccp');
  //$steps = MformsSteps::getInstance($store);

  //$hazards = new Hazards();


  //dpm($store);

}
