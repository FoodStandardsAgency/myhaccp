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
    'preview' => array(
      'data' => '',
    ),
    'delete' => array(
      'data' => '',
    ),
  );
  $rows = array();
  // Prepare the empty text in case there aren't any rows.
  $empty = t('You haven\'t yet started a study. Would you like to !start', array(
    '!start' => l(t('start one now?'), 'tool/study/create'),
  ));
  // Only display this user's form instances.
  $query = db_select('mforms_storage', 'm')
    ->fields('m', array())
    ->condition('m.uid', $user->uid);
  $results = $query->execute()->fetchAll();
  foreach ($results as $delta => $result) {
    // Build out the rows.
    $edit = user_access('edit own myhaccp study') || user_access('edit any myhaccp study') ? l(t('Resume'), 'tool/study/' . $result->iid) : '';
    $preview = user_access('view own myhaccp study') || user_access('view any myhaccp study') ? l(t('Preview'), 'tool/study/' . $result->iid . '/preview') : '';
    $delete = user_access('delete own myhaccp study') || user_access('delete any myhaccp study') ? l(t('Delete'), 'tool/study/' . $result->iid . '/delete') : '';

    $rows[] = array(
      'data' => array(
        'created' => format_date($result->created, 'short'),
        'changed' => $result->changed ? format_date($result->changed, 'short') : 'Not updated',
        'edit' => $edit,
        'preview' => $preview,
        'delete' => $delete,
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

  if (!empty($rows)) {
    $output['new'] = array(
      '#type' => 'link',
      '#title' => 'Start a new study',
      '#href' => 'tool/study/create',
      '#attributes' => array(
        'class' => array('new-study'),
      ),
    );
  }
  return $output;
}

/**
 * Previews a study and allows for exporting as PDF.
 */
function myhaccp_study_preview($iid) {
  if (is_numeric($iid)) {
    // Check this study is valid.
    $study = myhaccp_study_get_all_stages_data($iid);
    if (!empty($study)) {
      // Create the PDF button/link.
      $output = '';
      $output .= myhaccp_add_pdf_link($iid);
      // We have a fully loaded study. Iterate over each stage (key) and process
      // it with the suitable function.
      foreach ($study as $stage => $data) {
        $output .= theme($stage, array('data' => $data));
      }
      return $output;
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
 * Returns a pdf link.
 *
 * @param int $iid
 *   The IID of the study to render as PDF.
 *
 * @return string
 *   The link to render the PDF.
 */
function myhaccp_add_pdf_link($iid) {
  return l(t('Create PDF'), "tool/study/$iid/pdf", array());
}

/**
 * Menu callback for starting a new study.
 */
function myhaccp_study_create() {
  global $user;
  $record = array(
    'uid' => $user->uid,
    'created' => time(),
  );
  // Write the new record.
  drupal_write_record('mforms_storage', $record);
  // Forward to the beginning of the form.
  drupal_goto('tool/study/' . $record['iid']);
}

/**
 * Menu callback for deleting a study.
 */
function myhaccp_study_delete($form, &$form_state, $iid) {
  $form['iid'] = array(
    '#type' => 'value',
    '#value' => $iid,
  );
  return confirm_form($form, t('Are you sure you want to delete this study?'), 'tool', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Submit function for deleting a study.
 */
function myhaccp_study_delete_submit($form, &$form_state) {
  global $user;

  $iid = $form_state['values']['iid'];

  // Check this user own this study.
  $query = db_select('mforms_storage', 'ms')
    ->fields('ms', array('uid'))
    ->condition('ms.iid', $iid);
  $result = $query->execute()->fetchCol(0);

  if ($result) {
    if (($result[0] !== $user->uid && !user_access('delete any myhaccp study')) || !user_access('delete own myhaccp study')) {
      drupal_set_message('You don\'t have access to edit this study', 'error');
      drupal_goto('tool');
    }
  }
  else {
    drupal_set_message('This study cannot be found.');
  }

  // Delete all the associated form stages in mforms_storage_steps.
  db_delete('mforms_storage_steps')
    ->condition('iid', $iid)
    ->execute();

  // Delete the study from mforms_storage.
  db_delete('mforms_storage')
    ->condition('iid', $iid)
    ->execute();

  drupal_set_message(t('The study has been deleted.'));
  // Forward to the beginning of the form.
  drupal_goto('tool');
}
