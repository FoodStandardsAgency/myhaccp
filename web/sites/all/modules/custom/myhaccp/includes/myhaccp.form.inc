<?php

/**
 * Callback: Process form elements to add errors.
 *
 * Checks the form state's storage array element for a validate entry and then
 * tries to match it's key to the current form element's #name attribute. If
 * there is a match then it adds the error class to the form element and also
 * prints a message if the form has been executed. This ensures the message
 * only appears on the current stage.
 *
 * @see myhaccp_element_info_alter()
 */
function myhaccp_process($element, &$form_state) {
  if (isset($form_state['values']['validate'])) {
    $validation = reset($form_state['values']['validate']);
    // Add the error class to each of the elements.
    foreach ($validation as $target => $message) {
      $target_parts = explode('.', $target);
      if (!empty($element['#parents'])) {
        // Check that the intersection of the target and the current element's
        // parents array are the same. If they are then this is the element we
        // want to operate on.
        if (count(array_intersect($target_parts, $element['#parents'])) == count($target_parts)) {
          // Set the error attribute.
          $element['#attributes']['class']['error'] = 'error';
          if (!empty($message) && $form_state['executed'] == TRUE && $element['#type'] !== 'radio') {
            // Add the message inline.
            $element['#validation_message'] = $message;
          }
        }
      }
    }
  }
  return $element;
}

/**
 * Process function which handles validation messages and the page title.
 *
 * @param array $form
 *   The form array to modify.
 * @param array $form_state
 *   The form_state array to get the validation from.
 *
 * @return array
 *   The modified form array.
 */
function myhaccp_form_process($form, $form_state) {
  // Get the title of the page.
  $title = drupal_get_title();
  // Add the title in as a new markup element.
  $form['title'] = array(
    '#markup' => '<h1>' . $title . '</h1>',
    '#weight' => -20,
  );
  
  // First check for validation messages.
  if (isset($form_state['values']['validate'])) {
    // Ensure that these validations apply to this form. We ensure this
    // by making sure the key of the element below validate is used in the
    // current form array.
    $stage = key($form_state['values']['validate']);
    if (!isset($form[$stage])) {
      // The key wasn't found so return the form.
      return $form;
    }
    // The validation will be the only element under validate.
    $validation = reset($form_state['values']['validate']);
    // Provide an intro.
    $messages = array(
      'intro' => 'The following items have errors you will need to correct:',
    );

    // Add any messages that aren't associated with fields, so called 'global'
    // validation messages.
    foreach ($validation as $target => $message) {
      $element = array_get($form, $target, FALSE);
      if ($element && isset($element['#title'])) {
        $message = $element['#title'];
      }
      $messages[$target] = $message;
    }
    // If we already have validation messages then merge ours.
    if (isset($form['validation_messages']['#validation_message'])) {
      array_merge($form['validation_messages']['#validation_message'], $messages);
    }
    else {
      // Otherwise set the messages.
      $form['validation_messages']['#validation_message'] = $messages;
    }
  }

  return $form;
}
