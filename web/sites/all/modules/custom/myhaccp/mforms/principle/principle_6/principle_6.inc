<?php

/**
 * Principle 6.
 */
function principle_6(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_7';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_6');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 6: Verification');

  $form = array();
  $form['#attributes']['class'][] = 'principle-6';

  // Wrap the form section in a fieldset.
  $form['principle_6'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $store = mforms_store_get('myhaccp');
  // Fetch the previous step data.
  $steps = MformsSteps::getInstance($store);
  $prev_step = $steps->getPrev();

  // Create the fieldset container.
  $form['principle_6'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Now the form fields.
  $form['principle_6']['document'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('1. Document your validation study in the space below.'),
    '#help_text' => t('Provide details of all validation studies carried out.'),
    '#default_value' => array_get($values, "principle_6.document", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please add documentation of your validation study.'),
    ),
  );

  $form['principle_6']['responsible'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. Who is responsible for ensuring the contents of the HACCP plan are validated?'),
    '#help_text' => t('Enter the name of the person  responsible.'),
    '#default_value' => array_get($values, "principle_6.responsible", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state who is responsible for ensuring the contents of the HACCP plan are validated.'),
    ),
  );

  $form['principle_6']['trained'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('3. Is this the same person who will formally sign off the HACCP plan?'),
    '#help_text' => t('Enter the name of the person.'),
    '#default_value' => array_get($values, "principle_6.trained", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please indicate if this is the same person who will formally sign off the HACCP plan.'),
    ),
  );

  $form['principle_6']['sign_off'] = array(
    '#type' => 'textfield',
    '#title' => t('3a. Who will formally sign off the HACCP plan?'),
    '#default_value' => array_get($values, "principle_6.sign_off", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please state who is responsible for ensuring the contents of the HACCP plan are validated.'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="principle_6[trained]"]' => array('value' => 'no'),
      ),
    ),
  );

  $form['principle_6']['verification'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="label">What verification activities do you carry out? Mark all those that apply.</div>',
  );

  $form['principle_6']['verification']['internal'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Internal audits of'),
    '#options' => array(
      'ccps' => 'Critical Control Points',
      'prerequisites' => 'Prerequisites',
      'records' => 'Records of monitoring',
      'corrective' => 'Corrective actions',
    ),
    '#default_value' => array_get($values, "principle_6.verification.internal", array()),
  );

  $form['principle_6']['verification']['external'] = array(
    '#type' => 'checkboxes',
    '#title' => t('External auditing programmes'),
    '#options' => array(
      'supplier' => 'Supplier audits'
    ),
    '#default_value' => array_get($values, "principle_6.verification.external", array()),
  );

  $form['principle_6']['verification']['finished'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Finished product'),
    '#options' => array(
      'microbial' => 'Microbiological testing',
      'chemical' => 'Chemical testing',
    ),
    '#default_value' => array_get($values, "principle_6.verification.finished", array()),
  );

  $form['principle_6']['verification']['interim'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Interim product'),
    '#options' => array(
      'microbial' => 'Microbiological testing',
      'chemical' => 'Chemical testing',
    ),
    '#default_value' => array_get($values, "principle_6.verification.interim", array()),
  );

  $form['principle_6']['verification']['other'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Other'),
    '#options' => array(
      'monitoring' => 'Environmental monitoring of production area',
      'findings' => 'Addressing the findings of customer and third party audits',
      'third_party' => 'Third party certification(SOFHT, BRC)',
      'trending' => 'Trending and analysing customer complaints',
      'buy' => 'Product buy - back(buying your product from end point in market place and sampling and testing it for unexpected safety problems',
    ),
    '#default_value' => array_get($values, "principle_6.verification.other", array()),
  );

  $form['principle_6']['verification']['reviewing'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Reviewing'),
    '#options' => array(
      'deviations' => 'Deviations',
      'corrective' => 'Corrective actions',
      'disposal' => 'Product disposal',
      'rework' => 'Rework',
      'trending' => 'Trending of monitoring results',
    ),
    '#default_value' => array_get($values, "principle_6.verification.reviewing", array()),
  );

  $form['principle_6']['list'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('List any other verification activities carried out in your organisation.'),
    '#help_text' => t('If you carry out additional verification activities not listed above, record them here.'),
    '#default_value' => array_get($values, "principle_6.document", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please list any other verification activities carried out in your organisation.'),
    ),
  );

  $form['principle_6']['maintained'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('Are all verification records maintained?'),
    '#help_text' => t('You should keep verification records for a minimum of the life of a product  plus an extension period of ‘typically’ 3 months.  You must take into consideration abuse of your product and may wish to keep records for a longer period.'),
    '#default_value' => array_get($values, "principle_6.maintained", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm that all verification records are maintained.'),
    ),
  );

  $form['principle_6']['reviewed'] = array(
    '#type' => 'textfield',
    '#title' => t('How often is the HACCP system formally reviewed?'),
    '#help_text' => t('Is this annually, bi-annually or more frequently?'),
    '#default_value' => array_get($values, "principle_6.reviewed", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please detail how often the HACCP system is formally reviewed.'),
    ),
  );

  $form['principle_6']['responsible_review'] = array(
    '#type' => 'textfield',
    '#title' => t('Who is responsible for carrying out a formal annual review?'),
    '#help_text' => t('Provide name of individual responsible.'),
    '#default_value' => array_get($values, "principle_6.responsible_review", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state who is responsible for carrying out a formal annual review.'),
    ),
  );

  $form['principle_6']['triggers'] = array(
    '#type' => 'checkboxes',
    '#title' => t("Mark any of the following 'triggers' that will initiate a review in your organisation:"),
    '#options' => array(
      'advances' => 'Technological advances in production',
      'controls' => 'New controls that become available',
      'changes' => 'Change in raw material/ingredients/product formulation/packaging',
      'changes_supplier' => 'Change of raw material supplier',
      'changes_processing' => 'Change in processing system (e.g. changes in method of preservation – such as addition of preservatives, water activity changes, going from a sterilisation to a pasteurisation activity)',
      'changes_layout' => 'Changes in layout and environment of the factory',
      'modification' => 'Modification to process equipment (e.g. new equipment, modification of existing equipment)',
      'changes_cleaning' => 'Changes in cleaning and disinfection programme (i.e. a change to any supporting prerequisite programme)',
      'failuers' => 'Failures in the system, e.g. corrective actions or the need for product recall/withdrawal',
      'changes_storage' => 'Changes in the storage and distribution systems',
      'changes_staff' => 'Changes in staff levels and/or responsibilities',
      'anticipated' => 'Anticipated change in use of product by customer/consumer',
      'receipt' => 'Receipt of information from the market place indicating a health risk associated with the product',
      'emergence' => 'Emergence of foodborne pathogens with public health significance',
      'changes_legislation' => 'Changes in legislation',
      'scientific' => 'New scientific/technical knowledge (e.g. new information on hazards and control measures)',
      'unexpected' => 'Unexpected use of product by the consumer',
      'changes_environmental' => 'Environmental changes/issues (i.e. local changes external to the food operation; climate changes)',
    ),
    '#help_text' => t('If any of the items listed occur  your HACCP plan may not be valid and your product potentially unsafe.  In such a case it would be necessary to trigger a review.'),
    '#default_value' => array_get($values, "principle_6.triggers", array()),
  );

  $form['principle_6']['mechanisms'] = array(
    '#type' => 'textfield',
    '#title' => t("List any other mechanisms which are in place to automatically 'trigger' a review."),
    '#default_value' => array_get($values, "principle_6.mechanisms", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please list any other mechanisms which are in place to automatically ‘trigger’ a review.'),
    ),
  );

  $form['principle_6']['records_reviews'] = array(
    '#type' => 'radios',
    '#title' => t('Are all records from reviews documented, brought to the attention of senior management (for companies where this is appropriate)  and used to keep the HACCP plan up-to-date?'),
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#default_value' => array_get($values, "principle_6.records_reviews", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if all records from reviews documented, brought to the attention of senior management (for companies where this is appropriate) and used to keep the HACCP plan up-to-date.'),
    ),
  );

  // Add the validation handler.
  $form['#validate'][] = 'principle_6_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_6_validate($form, &$form_state) {
  $validator = new validator($form, $form_state, 'principle_6');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $checks = array(
    'principle_6.document' => 'fieldIsNotEmpty',
    'principle_6.responsible' => 'fieldIsNotEmpty',
    'principle_6.trained' => 'fieldIsNotEmpty',
    'principle_6.maintained' => 'fieldIsNotEmpty',
    'principle_6.reviewed' => 'fieldIsNotEmpty',
    'principle_6.responsible_review' => 'fieldIsNotEmpty',
    'principle_6.records_reviews' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  // Now check if the radio button in 3 is set to yes.
  if (array_get($form_state['values'], "principle_6.trained", FALSE) == 'yes') {
    // Now check that the dependent fields 5a has something in it.
    $validator->validate('fieldIsNotEmpty', 'principle_6.sign_off');
  }

  $validator->setErrorMessages();

}

