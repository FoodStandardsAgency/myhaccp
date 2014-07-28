<?php
/**
 * @file
 * Drupal strength constraint for Password Policy module.
 */

$plugin = array(
  'admin form callback' => 'password_policy_drupal_strength_admin_form',
  'constraint callback' => 'password_policy_drupal_strength_constraint',
  'message' => t('Password must match a Drupal strength level.'),
  'prime value' => 'drupal_strength',
  'config' => array(
    'drupal_strength' => NULL,
  ),
);

/**
 * Admin form callback for Drupal strength constraint.
 */
function password_policy_drupal_strength_admin_form($form, &$form_state, $constraint) {
  $sub_form['drupal_strength_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal strength'),
  );
  $sub_form['drupal_strength_fieldset']['drupal_strength'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal strength level'),
    '#default_value' => $constraint->config['drupal_strength'],
    '#description' => t('Password will be required to have match this level or higher. 0 - 100'),
  );

  return $sub_form;
}

/**
 * Constraint callback for Drupal strength constraint.
 */
function password_policy_drupal_strength_constraint($password, $account, $constraint) {
  $weaknesses = 0;
  $strength = 100;
  $has_lowercase = preg_match('/[a-z]+/', $password);
  $has_uppercase = preg_match('/[A-Z]+/', $password);
  $has_numbers = preg_match('/[0-9]+/', $password);
  $has_punctuation = preg_match('/[^a-zA-Z0-9]+/', $password);
  // Lose 5 points for every character less than 6, plus a 30 point penalty.
  if (strlen($password) < 6) {
    $strength -= ((6 - strlen($password)) * 5) + 30;
  }
  // Count weaknesses.
  if (!$has_lowercase) {
    $weaknesses++;
  }
  if (!$has_uppercase) {
    $weaknesses++;
  }
  if (!$has_numbers) {
    $weaknesses++;
  }
  if (!$has_punctuation) {
    $weaknesses++;
  }
  // Apply penalty for each weakness (balanced against length penalty).
  switch ($weaknesses) {
    case 1:
      $strength -= 12.5;
      break;

    case 2:
      $strength -= 25;
      break;

    case 3:
      $strength -= 40;
      break;

    case 4:
      $strength -= 40;
      break;
  }
  // Check if password is the same as the username.
  if ($password !== '' && strtolower($password) === strtolower($account->name)) {
    // Passwords the same as username are always very weak.
    $strength = 5;
  }
  return $strength >= $constraint->config['drupal_strength'];
}
