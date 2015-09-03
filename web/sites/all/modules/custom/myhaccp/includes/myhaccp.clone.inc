<?php

/**
 * @file
 * Function which help with cloning a study.
 */

/**
 * Given an IID will make a clone of a study.
 *
 * After the study is cloned the user is forwarded to the intro stage to fill
 * in their new study name.
 *
 * @param int $iid
 *   The IID of the study being cloned.
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

/**
 * The form displayed when the copy an existing study button is clicked.
 *
 * Displays a form allowing a user to select an existing study to copy.
 */
function myhaccp_study_copy_form($form, $form_state) {
  $form = array();

  $form['#attributes']['class'] = array('study-copy-form');

  drupal_set_title(t('Copy an existing study'));

  $path = libraries_get_path('qtip2');
  if ($path) {
    $form['#attached']['js'][] = $path . '/jquery.qtip.js';
    $form['#attached']['js'][] = drupal_get_path('module', 'myhaccp') . '/mforms/js/qtip2_custom.js';
    $form['#attached']['css'][] = $path . '/jquery.qtip.min.css';
  }

  global $user;

  $business = new business();
  $business->setUser($user);

  $form['studies'] = array(
    '#title' => t('Please choose an existing study to copy'),
    '#type' => 'select',
    '#options' => $business->getStudiesOptionsArray($user),
    '#help_text' => t("When you click the submit button, the existing study you
    have chosen will be copied. You will then be taken to the Preparatory Introduction stage of this new study where you can enter the new study's name."),
  );

  $form['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array(
      'class' => array(
        'form-actions',
        'form-wrapper',
        'container-inline'
      )
    ),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
  );

  return $form;
}

function myhaccp_study_copy_form_submit($form, $form_state) {
  switch ($form_state['values']['op']) {
    case 'Submit':
      $iid = $form_state['values']['studies'];
      myhaccp_study_clone($iid);
      break;

    case 'Cancel':
      drupal_goto('/tool');
      break;
  }
}