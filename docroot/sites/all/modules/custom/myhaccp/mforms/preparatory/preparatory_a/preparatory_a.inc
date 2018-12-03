<?php

/**
 * @file
 * Preparatory A stage form and validation handler.
 */

/**
 * Preparatory A.
 */
function preparatory_a(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_b';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_a');

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

  $form = array();
  $form['#attributes']['class'][] = 'prep-a';

  // Wrap the form section in a fieldset.
  $form['preparatory_a'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  $form['preparatory_a']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('Prior to the application of HACCP based food safety controls you should consider the prerequisite food hygiene requirements for your business.'),
  );

  $form['preparatory_a']['a_1'] = array(
    '#type' => 'checkboxes',
    '#title' => t('1. Select the boxes where you can demonstrate that you have control of the prerequisites.'),
    '#help_link' => 13,
    '#help_text' => t("These are 'pre-requirements' to the application and implementation of a HACCP system, to demonstrate you have control they should be well established, fully operational (including records) and verified."),
    '#options' => array(
      'Supplier approval' => t('Supplier approval'),
      'Packaging' => t('Packaging'),
      'Incoming material specifications' => t('Incoming material specifications'),
      'Finished product specification' => t('Finished product specification'),
      'Training (incl. training needs analysis, job descriptions)' => t('Training (incl. training needs analysis, job descriptions)'),
      'Contract services (i.e. waste/laundry)' => t('Contract services (i.e. waste/laundry)'),
      'Pest Control' => t('Pest Control'),
      'Glass and plastic management' => t('Glass and plastic management'),
      'Calibration' => t('Calibration'),
      'Standard Operating Procedures (SOPs)' => t('Standard Operating Procedures (SOPs)'),
      'Distribution' => t('Distribution'),
      'Product recall' => t('Product recall'),
      'Document control' => t('Document control'),
      'Audit schedule (incl. HACCP/internal audits)' => t('Audit schedule (incl. HACCP/internal audits)'),
      'Customer complaints' => t('Customer complaints'),
      'Tracking non-conformances' => t('Tracking non-conformances'),
      'Microbiological control' => t('Microbiological control'),
      'Preventative maintenance' => t('Preventative maintenance'),
      'Traceability' => t('Traceability'),
      'Utilities (air, water, energy)' => t('Utilities (air, water, energy)'),
      'Equipment suitability, cleaning and maintenance' => t('Equipment suitability, cleaning and maintenance'),
      'Measures to prevent cross-contamination' => t('Measures to prevent cross-contamination'),
      'Cleaning and sanitising' => t('Cleaning and sanitising'),
      'Personnel hygiene and employee facilities' => t('Personnel hygiene and employee facilities'),
      'Rework' => t('Rework'),
      'Warehousing' => t('Warehousing'),
      'Product information / consumer awareness' => t('Product information / consumer awareness'),
      'Food defence incl. Biovigilance and bioterrorism' => t('Food defence incl. Biovigilance and bioterrorism'),
      'Contamination control' => t('Contamination control'),
      'Return to work' => t('Return to work'),
      'Other' => t('Other'),
    ),
    '#default_value' => array_get($values, 'preparatory_a.a_1', array()),
    '#attributes' => array(
      'data-parsley-group' => 'checkgroup',
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please choose at least one option from the prerequisites field.'),
      'data-parsley-error-container' => '#edit-prep-a-a_1',
    ),
  );

  $form['preparatory_a']['a_1_1'] = array(
    '#type' => 'textarea',
    '#title' => t('1a. Please specify any other prerequisites.'),
    '#default_value' => array_get($values, "preparatory_a.a_1_1", FALSE),
    '#states' => array(
      'visible' => array(
        ':input[name="preparatory_a[a_1][Other]"]' => array('checked' => TRUE),
      ),
    ),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('You have selected other, please specify any other prerequisites.'),
    ),
  );

  // @ignore comment_comment_eg:function
  $form['preparatory_a']['a_2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. Please specify the location of the above documents.'),
    '#help_text' => t("State where you have stored the information.  You may wish to specify a manual e.g. manual of prerequisites,  where information on these is filed e.g. all documents filed under prerequisites, cabinet 1 or reference a particular document e.g.  PRP 01."),
    '#help_link' => 13,
    '#default_value' => array_get($values, 'preparatory_a.a_2', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Enter the location of your documents.'),
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_a_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $_myhaccp_container;
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

  // Validation: Some content.
  $checks = array(
    'preparatory_a.a_1' => 'fieldIsNotEmpty',
    'preparatory_a.a_2' => 'fieldIsNotEmpty',
  );

  if ($checkboxes = array_get($form_state['values'], 'preparatory_a.a_1', FALSE)) {
    if (isset($checkboxes['Other']) && $checkboxes['Other'] === 'Other') {
      $checks['preparatory_a.a_1_1'] = 'fieldIsNotEmpty';
    }
  }

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
