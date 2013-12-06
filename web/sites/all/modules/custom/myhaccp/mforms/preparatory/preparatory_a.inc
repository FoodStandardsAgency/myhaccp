<?php

function preparatory_a(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_1';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  if (!empty($data)) {
    $vals = $data;
  }
  elseif (isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  drupal_set_title('Preparatory Stage A: Prerequisites');

  $form = array();

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
  );

  $form['container']['options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Mark all boxes where you can demonstrate that you have control of the prerequisites !tip', array(
      '!tip' => _help_tip(),
    )),
    '#options' => drupal_map_assoc(array(
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
      )
    ),
  );

  $form['container']['prep1_location'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('Please specify the location of the above documents. !tip', array(
      '!tip' => _help_tip(),
    )),
  );

  return $form;
}
