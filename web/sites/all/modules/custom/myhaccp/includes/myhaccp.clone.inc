<?php

/**
 * @file
 * Function which help with cloning a study.
 */

function myhaccp_study_clone($iid) {
  global $container;
  $study = $container['study'];
  $new_iid = $study->cloneStudy($iid);
  $study->setCurrentStudy($new_iid);
  drupal_set_message(t('The study has been copied successfully. You are now on the Preparatory Introduction stage of your new study. Please name your new study.'));
  drupal_goto('/tool/study/' . $new_iid . '/preparatory/introduction', array(
    'query' => array(
      'new' => 'true',
    ),
  ));
}