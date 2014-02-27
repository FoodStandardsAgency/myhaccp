<?php

/**
 * Principle 4.
 */
function principle_4(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_5';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_4');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-4';

  // Wrap the form section in a fieldset.
  $form['principle_4'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $hazards = Hazards::getInstance();

  // Ensure there are hazards over the threshold.
  if ($hazards->countHazardsOverThreshold() == 0) {
    drupal_set_message('You have no significant hazards so you cannot continue', 'error');
    return $form;
  }

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 3.
  $ccps = $hazards->getCCPs();

  $instance_count = count($ccps);

  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You have no critical control points so you cannot continue');
    return $form;
  }

  // Build out the instances.
  foreach ($ccps as $hazard_key => $hazard) {
    $header = $hazard->getHeader();

    // Create the instance container.
    $form['principle_4'][$hazard_key] = array(
      '#type' => 'container',
    );

    $form['principle_4'][$hazard_key] += $header;

    // Now the form fields.
    $form['principle_4'][$hazard_key]['4_1'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('1. What monitoring activities are going to take place at this CCP?'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_1", FALSE),
      '#help_text' => t("Monitoring activities are  observations or measurements that must be able to detect loss of control at a CCP."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state what monitoring activities are going to take place at this CCP.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_2'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('2. Specify how frequently the monitoring activities are to be carried out.'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_2", FALSE),
      '#help_text' => t("e.g. every 20 minutes, ½ hourly, continually."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please specify  how frequently the monitoring activities are to be carried out.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_3'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('3. Define how the monitoring activities are carried out.'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_3", FALSE),
      '#help_text' => t("Specify how the monitoring activity is going to be performed."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please define how the monitoring activities are carried out.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_4'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('4. Who is responsible for monitoring actions at this CCP?'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_4", FALSE),
      '#help_text' => t("Name or individual/s authorised to carry out this task.  They must be trained and competent in being able to carry out this task."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state who is responsible for monitoring actions at this CCP.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_5'] = array(
      '#type' => 'textfield',
      '#title' => t('5. Please state the name and job title of the deputy if applicable:'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_5", FALSE),
      '#help_text' => t("Will anyone else carry out this monitoring activity in the absence of the main person responsible.  The deputy must be trained and competent to be able to perform the task."),
    );

    $form['principle_4'][$hazard_key]['4_6'] = array(
      '#type' => 'textfield',
      '#title' => t('6. Where are the results of monitoring recorded?'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_6", FALSE),
      '#help_text' => t("E.g. Is this in a specific log book, if so does it have a reference number or name?"),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state where the results of monitoring are recorded.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_7'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('7. Will the monitoring records be checked and signed off by anyone?'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_7", FALSE),
      '#help_text' => t("It is good practice to get someone who is trained and competent to check monitoring records and sign them off.  This is typically someone different to the person carrying out  the monitoring activity.  Signing them off would indicate that all records are within tolerance or if not, appropriate action has been taken."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state if the monitoring records are to be checked and signed off by anyone.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_7a'] = array(
      '#type' => 'textfield',
      '#title' => t('7a. Who will check the records?'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_7a", FALSE),
      '#help_text' => t("Name of person who is competent and trained t check records are completed as expected."),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_4[' . $hazard_key . '][4_7]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please state who will check the records.'),
      ),
    );

    $form['principle_4'][$hazard_key]['4_7b'] = array(
      '#type' => 'textfield',
      '#title' => t('7b. How frequently will they check the records?'),
      '#default_value' => array_get($values, "principle_4.$hazard_key.4_7b", FALSE),
      '#help_text' => t("E.g. daily."),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_4[' . $hazard_key . '][4_7]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please state how frequently the records will be checked.'),
      ),
    );

  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_4_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_4_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getStage('preparatory_a');
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_4', array());
  // Iterate over each row.
  foreach ($rows as $key => $row) {

    // Check for content in visible questions.
    $checks = array(
      "principle_4.$key.4_1" => 'fieldIsNotEmpty',
      "principle_4.$key.4_2" => 'fieldIsNotEmpty',
      "principle_4.$key.4_3" => 'fieldIsNotEmpty',
      "principle_4.$key.4_4" => 'fieldIsNotEmpty',
      "principle_4.$key.4_5" => 'fieldIsNotEmpty',
      "principle_4.$key.4_6" => 'fieldIsNotEmpty',
      "principle_4.$key.4_7" => 'fieldIsNotEmpty',
    );

    foreach ($checks as $target => $method) {
      $validator->validate($method, $target);
    }

    // Now check if the radio button in 5 is set to yes.
    if (array_get($form_state['values'], "principle_4.$key.4_5", FALSE) == 'yes') {
      // Now check that the dependent fields 5a has something in it.
      $validator->validate('fieldIsNotEmpty', "principle_4.$key.4_5a");
    }

    // Now check if the radio button in 7 is set to yes.
    if (array_get($form_state['values'], "principle_4.$key.4_7", FALSE) == 'yes') {
      // Now check that both dependent fields 7a and 7b have something in them.
      $checks = array(
        "principle_4.$key.4_7a" => 'fieldIsNotEmpty',
        "principle_4.$key.4_7b" => 'fieldIsNotEmpty',
      );

      foreach ($checks as $target => $method) {
        $validator->validate($method, $target);
      }
    }
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();

}

