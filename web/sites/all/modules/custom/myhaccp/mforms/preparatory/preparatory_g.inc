<?php

function preparatory_g(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_h';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_g');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage G: Construct a flow diagram', PASS_THROUGH);

  $default_file = array_get($values, 'preparatory_g.upload', FALSE);
  $default_file = $default_file ? $default_file['fid'] : FALSE;

  $form = array();
  $form['#attributes']['class'][] = 'prep-g';

  // Wrap the form section in a fieldset.
  $form['preparatory_g'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Have you completed a flow diagram?
  $form['preparatory_g']['flow_completed'] = array(
    '#type' => 'checkbox',
    '#prefix' => '<div class="label">' . t('1. Have you completed a flow diagram? !tip !help', array(
        '!tip' => _help_tip(20),
        '!help' => '<div class="help-text">This is a diagram showing <strong>all process steps</strong> in the manufacture of a product or the processing of a product.</div>',)) . '</div>',
    '#title' => t('I confirm that I have completed a flow diagram covering all steps in my manufacturing process.', array(
      //'!tip' => _help_tip(20),
    )),
    //'#help_text' => t('This is a diagram showing <strong>all process steps</strong> in the manufacture of a product or the processing of a product.'),
    '#default_value' => array_get($values, 'preparatory_g.flow_completed', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm that you have completed a flow diagram covering all steps in my manufacturing process.'),
    ),
  );

  global $user;

  // 2. If digital please upload.
  $form['preparatory_g']['upload'] = array(
    '#type' => 'managed_file',
    '#title' => t('2. Please upload a digital copy of your flow diagram (or go to 3). !tip', array(
      '!tip' => _help_tip(20),
    )),
    '#help_text' => t('This allows you to save your diagram on-line.'),
    '#default_value' => $default_file,
    '#progress_indicator' => 'bar',
    '#upload_location' => 'private://' . $user->uid,
    '#upload_validators' => array(
      'file_validate_extensions' => array('jpg', 'jpeg', 'png', 'pdf', 'gif'),
    ),
    '#attributes' => array(
      'data-parsley-error-message' => t('If a file is uploaded, it must be of type pdf, jpg, jpeg, png.'),
    ),
  );

  // 3. If digital please upload.
  $form['preparatory_g']['hard_copy'] = array(
    '#type' => 'textarea',
    '#title' => t('3. If you only have a hard copy, please  specify the location where it is retained and any document reference. !tip', array(
      '!tip' => _help_tip(20),
    )),
    '#help_text' => t('State where you can find the copy, e.g. HACCP file or filing cabinet under HACCP.'),
    '#default_value' => array_get($values, 'preparatory_g.hard_copy', FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('If you only have a hard copy, please specify the location where it is retained and any document reference.'),
    ),
  );

  $form['#validate'][] = 'preparatory_g_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_g_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $checks = array(
    'preparatory_g.flow_completed' => '_checkbox_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state);
  }

  if (_file_field_is_empty($form_state['values'], 'preparatory_g.upload') && _text_field_is_empty($form_state['values'], 'preparatory_g.hard_copy')) {
    $message = t('Please either upload a digital copy of your flow diagram, or if you only have a hard copy please specify the location where it is retained and any document reference.');
    myhacpp_prepare_validation('preparatory_g.upload', $message, $form_state);
    myhacpp_prepare_validation('preparatory_g.hard_copy', $message, $form_state);
    // Ensure validation errors aren't cleared.
    $invalid[] = TRUE;
  }

  if (array_get($form_state, 'values.preparatory_g.upload', FALSE)) {
    // Load the file via file.fid.
    $file = file_load($form_state['values']['preparatory_g']['upload']);
    if ($file->status != FILE_STATUS_PERMANENT) {
      // Change status to permanent.
      $file->status = FILE_STATUS_PERMANENT;
      // Save.
      file_save($file);
      // Get the current form's IID.
      $iid = $_SESSION['iid'];
      file_usage_add($file, 'myhaccp', 'form', $iid);
    }
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
