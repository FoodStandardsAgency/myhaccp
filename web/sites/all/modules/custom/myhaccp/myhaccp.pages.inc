<?php

/**
 * Menu callback which presents a table of forms to edit.
 */
function myhaccp_list() {

  drupal_set_title('MyHACCP Web Tool');

  $output['intro'] = array(
    '#type' => 'markup',
    '#markup' => t('Welcome to the MyHACCP Web Tool, from here you can start new studies and resume studies you have previously started. While using the Web Tool to undertake a Study you will find help available through help icons, which can be clicked on to reveal specific help for that question.')
  );

  global $user;
  // Prepare the table header.
  $header = array(
    'created' => array(
      'data' => 'Created on',
      'field' => 'created',
      'sort' => 'desc',
    ),
    'changed' => array(
      'data' => 'Last updated',
      'field' => 'changed',
    ),
    'edit' => array(
      'data' => '',
    ),
  );
  $rows = array();
  // Prepare the empty text in case there aren't any rows.
  $empty = t('You haven\'t yet started a study. Would you like to !start', array(
    '!start' => l(t('start one now?'), 'prototype/form/create'),
  ));
  // Only display this user's form instances.
  $query = db_select('mforms_storage', 'm')
    ->fields('m', array())
    ->condition('m.uid', $user->uid);
  $results = $query->execute()->fetchAll();
  foreach ($results as $delta => $result) {
    // Build out the rows.
    $edit = user_access('edit own myhaccp forms') || user_access('edit any myhaccp forms') ? l(t('Resume'), 'prototype/form/' . $result->iid) : '';
    $rows[] = array(
      'data' => array(
        'created' => format_date($result->created, 'short'),
        'changed' => $result->changed ? format_date($result->changed, 'short') : 'Not updated',
        'edit' => $edit,
      ),
    );
  }
  $output['table'] = array(
    '#type' => 'markup',
    '#markup' => theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'empty' => $empty,
      'attributes' => array(
        'class' => array('studies-table'),
      ),
    )),

  );
  $output['new'] = array(
    '#type' => 'link',
    '#title' => 'Start a new study',
    '#href' => 'prototype/form/create',
    '#attributes' => array(
      'class' => array('new-study'),
    ),
  );
  return $output;
}

/**
 * Menu callback for creating a form.
 */
function myhaccp_create() {
  global $user;
  $record = array(
    'uid' => $user->uid,
    'created' => time(),
  );
  // Write the new record.
  drupal_write_record('mforms_storage', $record);
  // Forward to the beginning of the form.
  drupal_goto('prototype/form/' . $record['iid']);
}

/**
 * Previews a study and allows for exporting as PDF.
 */
function myhaccp_preview() {
  if ($iid = arg(2)) {
    // Check this study is valid.
    $study = myhaccp_get_study($iid);
    if (!empty($study)) {
      $output = '';
      // We have a fully loaded study. Iterate over each stage (key) and process
      // it with the suitable function.
      foreach ($study as $stage => $data) {
        $output .= theme($stage, array('data' => $data));
        return $output;
      }
    }
    else {
      drupal_set_message('The requested study does not exist.', 'error');
    }
  }
  else {
    drupal_set_message('A study ID is required to preview a study.', 'error');
  }
}

/**
 * Gets the results of all the stages of the study.
 *
 * @param int $iid
 *   The study ID to preview.
 *
 * @return array
 *   An empty array if the IID wasn't found, otherwise an array keyed with the
 *   stage name and the values being the unserialized form state values.
 */
function myhaccp_get_study($iid) {
  // Fetch all the keys.
  $keys = _get_all_step_names();
  // Get all the stages from the db.
  $query = db_select('mforms_storage_steps', 'mss')
    ->fields('mss', array('store_key', 'store_data'))
    ->condition('mss.store_key', $keys, 'IN')
    ->condition('mss.iid', $iid);
  $results = $query->execute()->fetchAllAssoc('store_key');
  if ($results) {
    // Unpack the data into an array keyed by the stage name.
    asort($results);
    foreach ($results as $stage => $values) {
      $results[$stage] = unserialize($values->store_data);
    }
    // Sort it alphabetically and return it.
    return $results;
  }
  // Return an empty array if the study has not been found.
  return array();
}
