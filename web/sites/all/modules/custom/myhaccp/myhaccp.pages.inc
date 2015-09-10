<?php

/**
 * Menu callback which presents a table of forms to edit.
 */
function myhaccp_list() {

  drupal_set_title('MyHACCP Web Tool');

  $node = node_load(44);

  if ($node) {
    $node->title = NULL;
    $node_view = node_view($node, 'full');
    $output['intro'] = array(
      '#type' => 'markup',
      '#markup' => drupal_render($node_view),
    );
  }
  else {
    $output['intro'] = array(
      '#type' => 'markup',
      '#markup' => t('Welcome to the MyHACCP Web Tool, from here you can start new studies and resume studies you have previously started. While using the Web Tool to undertake a Study you will find help available through help icons, which can be clicked on to reveal specific help for that question.')
    );
  }

  global $user;
  // Prepare the table header.
  $header = array(
    'name' => array(
      'data' => 'Study name',
    ),
    'created' => array(
      'data' => 'Created on',
      'field' => 'm.created',
      'sort' => 'asc',
    ),
    'changed' => array(
      'data' => 'Last updated',
      'field' => 'm.changed',
    ),
    'status' => array(
      'data' => 'Status',
      'field' => 'm.status',
    ),
    'edit' => array(
      'data' => '',
    ),
    'options' => array(
      'data' => '',
    ),
  );

  // Prepare the rows.
  $rows = array();
  // Prepare the empty text in case there aren't any rows.
  $empty = t("You haven't yet started a study. Would you like to !start", array(
    '!start' => l(t('start one now?'), 'tool/study/create'),
  ));
  // Only display this user's form instances.
  $query = db_select('mforms_storage', 'm');
  $query->extend('TableSort')->orderByHeader($header);
  $query->fields('m', array())
    ->condition('m.uid', $user->uid);
  $results = $query->execute()->fetchAll();

  // Build out the rows.
  foreach ($results as $delta => $result) {

    // Set up a study for this result.
    $study = new Study();
    $study->setIID($result->iid);
    myhaccp_initialise_study($study);
    $validation_status = $study->getValidationStatus();

    // Prepare the edit link based on the current stage.
    $current_stage = $study->getCurrentStage();
    $study_name = $study->getName();
    // Be doubly sure we have both a stage object and that
    // its not empty.
    if (is_object($current_stage) && !empty($current_stage)) {
      // Get the stage url.
      $stage_url = $current_stage->getUrl();
    }
    else {
      // Fallback to a default url.
      $stage_url = 'preparatory_a';
    }
    $edit_link = 'tool/study/' . $result->iid . '/' . $stage_url;
    // Prepare the links.
    if ($study_name) {
      $name = user_access('edit own myhaccp study') || user_access('edit any myhaccp study') ? l($study_name, $edit_link) : $study_name;
    }
    else {
      $name = $study_name;
    }
    // The resume link.
    $edit = user_access('edit own myhaccp study') || user_access('edit any myhaccp study') ? l(t('Resume'), $edit_link, array(
      'attributes' => array(
        'class' => 'resume-link',
        'title' => t('Resume a study to add or edit your information.'),
      )
    )) : '';

    $options = array();
    $destination = drupal_get_destination();

    // Download the PDF.
    $options[] = array(
      'title' => t('Download'),
      'href' => 'tool/study/' . $result->iid . '/pdf',
      'attributes' => array(
        'class' => 'link--download',
      ),
    );

    // The complete link if possible.
    if (user_access('edit own myhaccp study') || user_access('edit any myhaccp study')) {
      if ($study->getStatus() == 0 && $validation_status == VALID) {
        // The study is currently incomplete but valid so present a complete
        // button to the user.
        $options[] = array(
          'title' => t('Complete'),
          'href' => 'tool/study/' . $result->iid . '/complete/1',
          'attributes' => array(
            'class' => 'link--complete',
            'data-valid' => $validation_status,
            'data-status' => $study->getStatus(),
            'title' => t('Mark your study as complete.'),
          ),
          'query' => $destination,
        );
      }
      elseif ($study->getStatus() == 1) {
        // The study is current in a complete state (but may be invalid) so
        // allow the user to change it to incomplete.
        $options[] = array(
          'title' => t('Activate'),
          'href' => 'tool/study/' . $result->iid . '/complete/0',
          'attributes' => array(
            'class' => 'link--complete',
            'data-valid' => $validation_status,
            'data-status' => $study->getStatus(),
            'title' => t('Re-activate a completed study.'),
          ),
          'query' => $destination,
        );
      }
    }

    // Clone a study.
    if (user_access('clone own myhaccp study') || user_access('clone any myhaccp study')) {
      $options[] = array(
        'title' => t('Copy'),
        'href' => 'tool/study/' . $result->iid . '/clone',
        'attributes' => array(
          'class' => 'link--clone',
          'data-valid' => $validation_status,
          'data-status' => $study->getStatus(),
        ),
      );
    }

    // The delete link.
    if (user_access('delete own myhaccp study') || user_access('delete any myhaccp study')) {
      $options[] = array(
        'title' => t('Delete'),
        'href' => 'tool/study/' . $result->iid . '/delete',
        'attributes' => array(
          'class' => 'link--delete',
          'data-valid' => $validation_status,
          'data-status' => $study->getStatus(),
          'title' => t('Delete your study.'),
        ),
      );
    }

    // Prepare the options dropdown button.
    $options_link = theme('ctools_dropdown', array(
      'title' => 'More options',
      'links' => $options,
      'class' => 'study-more-dropdown split-button',
    ));

    // Convert status integers to a word.
    $status = $result->status == 1 ? 'Complete' : 'Active';

    $rows[] = array(
      'data' => array(
        'name' => $name,
        'created' => format_date($result->created, 'short_date'),
        'changed' => $result->changed ? format_date($result->changed, 'short_date') : 'Not updated',
        'status' => $status,
        'edit' => $edit,
        'options' => $options_link,
      ),
    );
  }

  $output['new'] = array(
    '#type' => 'link',
    '#title' => 'Start a new study',
    '#href' => 'tool/study/create',
    '#attributes' => array(
      'class' => array('new-study'),
    ),
  );

  if (!empty($results)) {
    $output['copy'] = array(
      '#type' => 'link',
      '#title' => 'Copy an existing study',
      '#href' => 'tool/study/copy',
      '#attributes' => array(
        'class' => array('copy-study'),
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
      'sticky' => FALSE,
    )),

  );

  return $output;
}

/**
 * Given an IID tries to find which is the stored current stage.
 *
 * @param int $iid
 *   The IID of the study.
 *
 * @return string
 *   The stage name if found or an empty string.
 */
function myhaccp_find_current_stage($iid) {
  $data = db_select('mforms_storage', 'm');
  $data->join('mforms_storage_steps', 's', 's.iid = m.iid');
  $data->fields('s', array('store_data'))
    ->condition('m.iid', $iid)
    ->condition('s.store_key', 'curr_step');
  $result = $data->execute()->fetchField();
  if ($result) {
    $data = unserialize($result);
    return $data;
  }
  return '';
}

/**
 * Previews a study and allows for exporting as PDF.
 */
function myhaccp_study_preview($iid) {
  if (is_numeric($iid)) {
    // Make sure the IID exists in the session. Its possible to log in and
    // preview a document without the IID getting stored in the SESSION.
    $_SESSION['iid'] = $iid;
    myhaccp_myhaccp_mforms_init();
    // Get the dependency injection container.
    global $container;
    // Get the current study.
    $configuration = $container['configuration'];
    $keys = array_keys($configuration->getMachineNames());
    // Check this study is valid.
    $study = myhaccp_study_get_stages_data($keys, $iid);
    if (!empty($study)) {
      // Create the PDF button/link.
      $output = '';
      $output .= myhaccp_add_pdf_link($iid);
      // We have a fully loaded study. Iterate over each stage (key) and process
      // it with the suitable function.
      foreach ($study as $stage => $data) {
        $output .= theme($stage, array('data' => $data));
      }
      // Force the title to be set here.
      drupal_set_title('Study preview');
      return $output;
    }
    else {
      drupal_set_message('The requested study does not exist or has no data.', 'error');
      return '';
    }
  }
  else {
    drupal_set_message('A study ID is required to preview a study.', 'error');
    return '';
  }
}

/**
 * Presents a completion page for the study.
 *
 * @param int $iid
 *   The ID of the study.
 *
 * @return string
 *   The rendered page output.
 */
function myhaccp_study_finish($iid) {
  // Load the node with the text to show.
  $node = node_load(39);
  drupal_set_title($node->title);
  $node->title = NULL;
  $node_output = node_view($node, 'full');

  // Set up a study for this result.
  $study = new Study();
  $study->setIID($iid);
  myhaccp_initialise_study($study);
  $validation_status = $study->getValidationStatus();

  // Get the current page.
  $destination = drupal_get_destination();
  $complete = '';

  if ($study->getStatus() == 0 && $validation_status == VALID) {
    // The study is currently incomplete but valid so present a complete
    // button to the user.
    $complete = l(t("Mark your HACCP study as 'complete'"), 'tool/study/' . $study->getIID() . '/complete/1', array(
      'attributes' => array(
        'class' => 'complete-link',
        'data-valid' => $validation_status,
        'data-status' => $study->getStatus(),
      ),
      'query' => $destination,
    ));
  }
  elseif ($study->getStatus() == 1) {
    // The study is currently in a complete state (but may be invalid) so
    // allow the user to change it to incomplete.
    $complete = l(t("Mark your HACCP study as 'active'"), 'tool/study/' . $study->getIID() . '/complete/0', array(
      'attributes' => array(
        'class' => 'complete-link',
        'data-valid' => $validation_status,
        'data-status' => $study->getStatus(),
      ),
      'query' => $destination,
    ));
  }

  $download_text = $validation_status == VALID ? t('Download your HACCP study') : t('Download your incomplete HACCP study');
  // Offer a download link.
  $download = l($download_text, "tool/study/$iid/pdf", array(
    'attributes' => array(
      'class' => array('download-link'),
      'data-valid' => $validation_status,
      'data-status' => $study->getStatus(),
    ),
  ));

  // Output the page.
  $output = drupal_render($node_output);
  $output .= $complete . ' ' . $download;
  return $output;
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

/**
 * A simple menu callback to register a home page.
 *
 * The content on the home page is handled through block (bean) placement.
 */
function myhaccp_home() {
  return array();
}