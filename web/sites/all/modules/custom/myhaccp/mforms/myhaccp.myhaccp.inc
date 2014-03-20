<?php

/**
 * @file
 * Defines all of the step definitions.
 *
 * Each step is defined in this file and included in another file.
 */

/**
 * Ajax callback which returns the form array element to be applied against.
 */
function instance_add_more_callback($form, $form_state) {
  return $form['container'];
}

/**
 * Ajax submit handler which positively adjusts the number of instances.
 */
function instance_add_more_add_one($form, &$form_state) {
  $form_state['num_instances']++;
  // Trigger a form rebuilt with an increased number of instances.
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax submit handler which negatively adjusts the number of instances.
 */
function instance_add_more_remove_one($form, &$form_state) {
  if ($form_state['num_instances'] > 1) {
    $form_state['num_instances']--;
  }
  // Trigger a form rebuild.
  $form_state['rebuild'] = TRUE;
}

/**
 * Modify the form for each stage.
 *
 * Adds the parsley attributes to the form element. Also adds a save message
 * handler.
 */
function myhaccp_form_myhaccp_study_resume_alter(&$form, &$form_state) {
  $form['#attributes']['data-parsley-namespace'] = 'data-parsley-';
  $form['#attributes']['data-parsley-validate'] = '';
  // The message that says the stage has saved.
  $form['#validate'][] = 'myhaccp_saved_message';
  $form['#process']['myhaccp'] = 'myhaccp_form_process';
}

/**
 * Menu callback which marks a study as being complete or incomplete.
 *
 * @param int $iid
 *   The study to operate on.
 * @param int $status
 *   The status integer to store.
 */
function myhaccp_study_complete($iid, $status) {
  $study = new Study();
  $study->setIID($iid);
  myhaccp_initialise_study($study);
  // Get the validation status of the study.
  $valid_status = $study->getValidationStatus();
  if ($status == 0) {
    $study->setStatus(0);
    drupal_set_message(t("You have set the completion status of the study to 'started'."));
  }
  else {
    // The user is trying to mark this study as complete.
    if ($valid_status == INVALID) {
      drupal_set_message(t('As there are incomplete stages of the study you are unable to mark it as complete yet. Please resume the study and use the review pages to determine which stages need work to complete.'), 'error');
    }
    else {
      $study->setStatus(1);
      drupal_set_message(t("You have set the completion status of the study to 'complete'."));
    }
  }
  drupal_goto();
}
