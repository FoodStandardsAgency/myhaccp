<?php

function preparatory_review(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_1';

  // Set the page title.
  $stages = new Stages();
  $stage = $stages->getStage(__FUNCTION__);
  drupal_set_title($stage->title, PASS_THROUGH);

  // Get the node output.
  $node = node_load(35);
  $node_output = node_view($node);
  $validation = new ValidateStages();
  // Get the statuses.
  $statuses = $validation->getPreparatoryStagesStatuses();
  $message_output = '';
  // Iterate over all the statuses of all the stages.
  foreach ($statuses as $key => $passed) {

    // Get the stage.
    $stage = $stages->getStage($key);

    // Construct a url to the stage.
    $url = 'tool/study/' . $_SESSION['iid'] . '/' . $stage->url;

    // Determine what is displayed and the class name for a pass or fail.
    if ($passed) {
      $state = t('OK');
      $class = 'passed';
    }
    else {
      $state = l(t('Needs review'), $url);
      $class = 'review';
    }

    $message_output .= '<div class="stage-validation ' . $class . '">';
    $message_output .= '<h3>' . $stage->title . '</h3>';
    $message_output .= '<div class="validation-status">' . $state . '</div>';
    $message_output .= '</div>';
  }

  $form = array();

  $form['preparatory_review'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['preparatory_review']['validation'] = array(
    '#type' => 'container',
  );

  $form['preparatory_review']['validation']['messages'] = array(
    '#markup' => $message_output,
  );


  $form['preparatory_review']['node'] = array(
    '#markup' => drupal_render($node_output),
  );

  return $form;
}
