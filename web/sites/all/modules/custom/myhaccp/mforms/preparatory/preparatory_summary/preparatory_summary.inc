<?php

function preparatory_summary(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_1';

  // Set the page title.
  $stages = new Stages();
  $stage = $stages->getStage(__FUNCTION__);
  drupal_set_title($stage->title, PASS_THROUGH);

  // Get the node output.
  $node = node_load(1);
  $node_output = node_view($node);
  $validation = new ValidateStages();
  $statuses = $validation->getPreparatoryStagesStatuses();
  $message_output = '';
  foreach ($statuses as $key => $state) {
    $message_output .= '<h3>' . $titles[$key] . '</h3>';
    $message_output .= '<div class="validation-status">' . $state . '</div>';
  }

  $form = array();

  $form['preparatory_summary'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['preparatory_summary']['validation'] = array(
    '#type' => 'container',
  );

  $form['preparatory_summary']['validation']['messages'] = array(
    '#markup' => $message_output,
  );


  $form['preparatory_summary']['node'] = array(
    '#markup' => drupal_render($node_output),
  );

  return $form;
}
