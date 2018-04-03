<?php

/**
 * @file
 * Preparatory G stage form and validation handler.
 */

/**
 * Preparatory G.
 */
function preparatory_g(&$form_state, &$next_step) {
  // @ignore comment_comment_eg:function

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_h';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_g');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  // Fetch the existing file if it exists.
  if (array_get($form_state, 'values.preparatory_g.g_2', FALSE)) {
    $default_file = array_get($form_state, 'values.preparatory_g.g_2', FALSE);
  }
  else {
    $default_file = array_get($values, 'preparatory_g.g_2', FALSE);
    if (is_array($default_file)) {
      $default_file = reset($default_file);
    }
  }

  $form = array();
  $form['#attributes']['class'][] = 'prep-g';

  // Wrap the form section in a fieldset.
  $form['preparatory_g'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  $form['preparatory_g']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('A process flow diagram shows all the steps involved in the process outlined in the scope  of  the study.'),
  );

  // 1. Have you completed a flow diagram?
  $form['preparatory_g']['g_1'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes', array(), array('context' => 'Have you completed a flow diagram?')),
      'no' => t('No', array(), array('context' => 'Have you completed a flow diagram?')),
    ),
    '#title' => t('1. Have you completed a flow diagram?'),
    '#help_link' => 20,
    '#help_text' => t('This is a diagram showing <strong>all process steps</strong> in the manufacture of a product or the processing of a product.'),
    '#default_value' => array_get($values, 'preparatory_g.g_1', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('It is strongly advised that you complete a flow diagram covering all steps in your manufacturing process before proceeding.'),
    ),
  );

  global $user;

  // 2. If digital please upload.
  $form['preparatory_g']['g_2'] = array(
    '#type' => 'managed_file',
    '#title' => t('2. Please upload a digital copy of your flow diagram (or go to 3).'),
    '#help_link' => 20,
    '#help_text' => t('This allows you to save your diagram on-line and will present it in the output document. Allowed file types are: jpg, jpeg, png and pdf.'),
    '#default_value' => $default_file,
    '#progress_indicator' => 'bar',
    '#upload_location' => 'private://' . $user->uid,
    '#process' => array(
      'file_managed_file_process',
      'preparatory_g_process',
    ),
    '#upload_validators' => array(
      'file_validate_extensions' => array('jpg jpeg png gif pdf'),
      'myhaccp_validate_image' => array(),
      'myhaccp_validate_pdf' => array(),
    ),
    '#attributes' => array(
      'data-parsley-error-message' => t('If a file is uploaded, it must be of type gif, jpg, jpeg, png or pdf.'),
    ),
  );

  // 3. If you only have a hard copy, please  specify the location where it is retained and any document reference.
  $form['preparatory_g']['g_3'] = array(
    '#type' => 'textarea',
    '#title' => t('3. If you only have a hard copy, please  specify the location where it is retained and any document reference.'),
    '#help_link' => 20,
    '#help_text' => t('State where you can find the copy, e.g. HACCP file or filing cabinet under HACCP.'),
    '#default_value' => array_get($values, 'preparatory_g.g_3', FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('If you only have a hard copy, please specify the location where it is retained and any document reference.'),
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_g_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Prepare the messages array.
  $messages = array();
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array(
    'preparatory_g.g_1' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  // Check that there is either an upload or a hard copy.
  $upload = new Validation($form, $form_state, 'preparatory_g.g_2');
  $hard_copy = new Validation($form, $form_state, 'preparatory_g.g_3');
  if (!$upload->fieldIsNotEmpty() && !$hard_copy->fieldIsNotEmpty()) {
    $messages['validation_messages'][] = t('Please either upload a digital copy of your flow diagram, or if you only have a hard copy please specify the location where it is retained and any document reference.');
    $validator->setStatus(FALSE);
  }

  // Make sure uploaded files are permanently stored.
  if (array_get($form_state, 'values.preparatory_g.g_2', FALSE)) {
    // Load the file via file.fid.
    $file = file_load($form_state['values']['preparatory_g']['g_2']);
    // Validate whether this file is really an image. Sometimes people upload
    // weird things renamed as images. Also allow PDFs to be permanently saved.
    if ($file->filemime == 'application/pdf' || image_load($file->uri)) {
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
    else {
      $messages['validation_messages'][] = t('2. Please upload a digital copy of your flow diagram (or go to 3). There was an error processing your uploaded flow diagram. Please ensure you only upload a PDF or an image file of the following formats: jpg, png, gif');
      $validator->setStatus(FALSE);
      $form_state['values']['preparatory_g']['g_2'] = FALSE;
      // Pass in the modified form_state.
      $validator->setFormState($form_state);
    }
  }

  $validator->setErrorMessages($messages);
  $form_state = $validator->getFormState();
}

/**
 * A process function which runs after file_managed_process.
 *
 * Used to change the filename to a thumbnail image.
 *
 * @param array $element
 *   The file element to modify.
 *
 * @return array
 *   The changed element.
 */
function preparatory_g_process(&$element, $form_state, $form) {
  if (!empty($form_state['input']['_triggering_element_value']) && $form_state['input']['_triggering_element_value'] == 'Remove') {
    return $element;
  }
  $fid = isset($element['#value']['fid']) ? $element['#value']['fid'] : 0;
  if ($fid && $element['#file']) {
    $element['filename'] = array(
      '#type' => 'markup',
      '#markup' => theme('myhaccp_preview_diagram', array('element' => $element)) . ' ',
      '#weight' => -10,
    );
    // Check the mimetype to determine what to show here.
    if ($element['#file']->filemime == 'application/pdf') {
      $element['filename']['#markup'] = theme('image', array(
        'path' => drupal_get_path('theme', 'myhaccp_theme') . '/images/pdf-icon.png',
        'alt' => t('PDF icon representing an uploaded file'),
      ));
    }
  }
  return $element;
}
