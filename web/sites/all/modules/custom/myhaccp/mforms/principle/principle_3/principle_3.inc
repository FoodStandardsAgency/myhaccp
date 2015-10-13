<?php

/**
 * @file
 * Principle 3 stage form and validation handler.
 */

/**
 * Principle 3.
 */
function principle_3(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_4';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_3');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-3';

  $hazards = Hazards::getInstance();

  // Ensure there are hazards over the threshold.
  if ($hazards->countHazardsOverThreshold() == 0) {
    drupal_set_message(t('You have no significant hazards so you cannot continue'), 'error');
    return $form;
  }

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 3.
  $ccps = $hazards->getCCPs();

  $instance_count = count($ccps);
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message(t('You have no critical control points so you cannot continue'));
    return $form;
  }

  // Create the fieldset container.
  $form['principle_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Introductory text.
  $form['principle_3']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('A critical limit is the maximum or minimum value for the control measure at a CCP to prevent, eliminate or reduce the hazard to an acceptable level. It separates acceptable (safe) from unacceptable (unsafe) product.'),
  );

  // Build out the instances.
  foreach ($ccps as $hazard_key => $hazard) {
    $header = $hazard->getHeader();

    // Create the instance container.
    $form['principle_3'][$hazard_key] = array(
      '#type' => 'container',
    );

    $form['principle_3'][$hazard_key] += $header;

    // Now the form fields.
    $form['principle_3'][$hazard_key]['3_1'] = array(
      '#type' => 'textfield',
      '#title' => t('1. What is the critical limit for this critical control point (what separates safe from potentially unsafe product)?'),
      '#help_text' => t('The critical limit is a value that separates acceptable from unacceptable e.g. 72 degrees Celsius (can we put this in units please) below this temperature the product is unacceptable above this limit it is considered acceptable.'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_1", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please specify the critical limit for this critical control point.'),
      ),
    );

    $form['principle_3'][$hazard_key]['3_2'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('2. Provide details of how the critical limit was determined.'),
      '#help_text' => t('Have you used legislation, industry guides, historical data?  List details of all resources used to arrive at the critical limit.'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_2", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please provide details of how the critical limit was determined.'),
      ),
    );

    $form['principle_3'][$hazard_key]['3_3'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes', array(), array('context' => 'Is the critical limit appropriate to control the specific hazard?')),
        'no' => t('No', array(), array('context' => 'Is the critical limit appropriate to control the specific hazard?')),
      ),
      '#title' => t('3. Is the critical limit appropriate to control the specific hazard?'),
      '#help_text' => t('Will the critical limit you have set prevent, reduce or eliminate the hazard identified?'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_3", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('It is essential that the critical limit is appropriate to control the specific hazard.'),
      ),
    );

    $form['principle_3'][$hazard_key]['3_4'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes', array(), array('context' => 'Is the critical limit measurable or observable in real time?')),
        'no' => t('No', array(), array('context' => 'Is the critical limit measurable or observable in real time?')),
      ),
      '#title' => t('4. Is the critical limit measurable or observable in real time?'),
      '#help_text' => t('Measurable examples include things like pH, aw, brix, psi and observable examples include boiling, colour change, steaming, size reduction.'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_4", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('It is essential that critical limit is measurable or observable in real time.'),
      ),
    );

    $form['principle_3'][$hazard_key]['3_5'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes', array(), array('context' => 'Is there a target value?')),
        'no' => t('No', array(), array('context' => 'Is there a target value?')),
      ),
      '#title' => t('5. Is there a target value?'),
      '#help_text' => t('This is more stringent than a critical limit but allows a business to gain control before a critical limit is breached.'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_5", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please indicate whether there is a target value.'),
      ),
    );

    $form['principle_3'][$hazard_key]['3_6'] = array(
      '#type' => 'textfield',
      '#title' => t('5a. If yes, what is the target value?'),
      '#help_text' => t('State the target value e.g.  74 degrees Celsius where the critical limit  is  72 degrees Celsius.'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_6", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_3[' . $hazard_key . '][3_5]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please specify the target value.'),
      ),
    );

    $form['principle_3'][$hazard_key]['3_7'] = array(
      '#type' => 'textfield',
      '#title' => t('5b. Please specify any tolerances'),
      '#help_text' => t('This is the value between the critical limit and the target value.'),
      '#help_link' => 29,
      '#default_value' => array_get($values, "principle_3.$hazard_key.3_7", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_3[' . $hazard_key . '][3_5]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please specify the tolerance.'),
      ),
    );

  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_3_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_3_validate($form, &$form_state) {
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

  $rows = array_get($form_state, 'values.principle_3', array());
  // Iterate over each row.
  foreach ($rows as $hazard_key => $row) {

    // Check for content in questions 1 & 2.
    $checks = array(
      "principle_3.$hazard_key.3_1" => 'fieldIsNotEmpty',
      "principle_3.$hazard_key.3_2" => 'fieldIsNotEmpty',
    );

    foreach ($checks as $target => $method) {
      $validator->validate($method, $target);
    }

    // Make sure 3 & 4 are yes values.
    $checks = array(
      "principle_3.$hazard_key.3_3" => array('fieldIsNotEmpty', 'radioIsNotNo'),
      "principle_3.$hazard_key.3_4" => array('fieldIsNotEmpty', 'radioIsNotNo'),
    );
    // Iterate over the two fields and check them.
    foreach ($checks as $target => $method) {
      $validator->validate($method, $target);
    }

    // Now check if the radio button in 5 is set to yes.
    if (array_get($form_state['values'], "principle_3.$hazard_key.3_5", FALSE) == 'yes') {
      // Now check that both dependent fields 5a and 5b have something in them.
      $checks = array(
        "principle_3.$hazard_key.3_6" => 'fieldIsNotEmpty',
      );

      foreach ($checks as $target => $method) {
        $validator->validate($method, $target);
      }
    }
    else {
      // Confirm this field is not empty.
      $validator->validate('fieldIsNotEmpty', "principle_3.$hazard_key.3_5");
    }
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
