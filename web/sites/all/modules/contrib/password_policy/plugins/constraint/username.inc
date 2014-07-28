<?php
/**
 * @file
 * Username constraint for Password Policy module.
 */

$plugin = array(
  'admin form callback' => 'password_policy_username_admin_form',
  'constraint callback' => 'password_policy_username_constraint',
  'message' => t('Password must not contain their username.'),
  'prime value' => 'username',
  'config' => array(
    'username' => FALSE,
  ),
);

/**
 * Admin form callback for username constraint.
 */
function password_policy_username_admin_form($form, &$form_state, $constraint) {
  $sub_form['username_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Username'),
  );
  $sub_form['username_fieldset']['username'] = array(
    '#type' => 'checkbox',
    '#title' => t('Password must not contain their username.'),
    '#default_value' => $constraint->config['username'],
  );

  return $sub_form;
}

/**
 * Constraint callback for username constraint.
 */
function password_policy_username_constraint($password, $account, $constraint) {
  // Pass constraint if there's no name such as when this policy is used on new
  // account registration.
  if (empty($account->name)) {
    return TRUE;
  }
  $regex_string = '/' . $account->name . '/';
  return !preg_match($regex_string, $password);
}
