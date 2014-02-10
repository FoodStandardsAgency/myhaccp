<?php

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

  drupal_set_title('Preparatory Stage A: Prerequisites');

  $form = array();
  $form['#attributes']['class'][] = 'prep-a';

  // Wrap the form section in a fieldset.
  $form['preparatory_a'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['preparatory_a']['prereq'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Mark all boxes where you can demonstrate that you have control of the prerequisites !tip', array(
      '!tip' => _help_tip(13),
    )),
    '#help_text' => t("These are 'pre-requirements' to the application and implementation of a HACCP system, to demonstrate you have control they should be well established, fully operational (including records) and verified."),
    '#options' => array_flip(drupal_map_assoc(array(
      t('Supplier approval'),
      t('Packaging'),
      t('Incoming material specifications'),
      t('Finished product specification'),
      t('Training (incl. training needs analysis, job descriptions)'),
      t('Contract services (i.e. waste/laundry)'),
      t('Pest Control'),
      t('Glass and plastic management'),
      t('Calibration'),
      t('Standard Operating Procedures SOP\'s'),
      t('Distribution'),
      t('Product recall'),
      t('Document control'),
      t('Audit schedule (incl. HACCP/internal audits)'),
      t('Customer complaints'),
      t('Tracking non-conformances'),
      t('Microbiological control'),
      t('Preventative maintenance'),
      t('Traceability'),
      t('Utilities (air, water, energy)'),
      t('Waste disposal'),
      t('Equipment suitability, cleaning and maintenance'),
      t('Measures to prevent cross-contamination'),
      t('Cleaning and sanitising'),
      t('Personnel hygiene and employee facilities'),
      t('Rework'),
      t('Warehousing'),
      t('Product information / consumer awareness'),
      t('Food defence incl. Biovigilance and bioterrorism'),
      t('Contamination control'),
      t('Return to work'),
      t('Other'),
      ), 'drupal_html_id'
    )),
    '#default_value' => array_get($values, 'preparatory_a.prereq', array()),
    '#attributes' => array(
      'data-parsley-group' => 'checkgroup',
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please choose at least one option from the prerequisites field.'),
      'data-parsley-error-container' => '#edit-prep-a-prereq',
    ),
  );

  $form['preparatory_a']['location'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('Please specify the location of the above documents. !tip', array(
      '!tip' => _help_tip(13),
    )),
    '#help_text' => t("State where you have stored the information.  You may wish to specify a manual e.g. manual of prerequisites,  where information on these is filed e.g. all documents filed under prerequisites, cabinet 1 or reference a particular document e.g.  PRP 01."),
    '#default_value' => array_get($values, 'preparatory_a.location', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Enter the location of your documents.'),
    ),
  );

  $form['#validate'][] = 'preparatory_a_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_a_validate($form, &$form_state) {
  // Only continue if there is some data in one or more fields.
  if (myhacpp_all_fields_are_empty($form_state, __FUNCTION__)) {
    return;
  }

  $invalid = array();

  // Validation: Some content.
  $checks = array(
    'preparatory_a.prereq' => '_checkboxes_field_is_empty',
    'preparatory_a.location' => '_text_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
