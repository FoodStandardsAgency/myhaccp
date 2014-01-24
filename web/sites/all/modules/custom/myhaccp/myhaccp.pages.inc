<?php

/**
 * Menu callback which presents a table of forms to edit.
 */
function myhaccp_list() {
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
      'data' => 'Resume a study',
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
  $output = array(
    'table' => array(
      '#type' => 'markup',
      '#markup' => theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'empty' => $empty,
      )),
    ),
    'new' => array(
      '#type' => 'link',
      '#title' => 'Start a new study',
      '#href' => 'prototype/form/create',
    )
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
