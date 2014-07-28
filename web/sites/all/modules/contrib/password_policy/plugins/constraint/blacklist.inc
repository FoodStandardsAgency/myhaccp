<?php
/**
 * @file
 * Blacklist constraint for Password Policy module.
 */

$plugin = array(
  'admin form callback' => 'password_policy_blacklist_admin_form',
  'constraint callback' => 'password_policy_blacklist_constraint',
  'message' => 'Password cannot match certain disallowed passwords.',
  'prime value' => 'blacklist',
  'config' => array(
    'blacklist' => '',
  ),
);

/**
 * Admin form callback for blacklist constraint.
 */
function password_policy_blacklist_admin_form($form, &$form_state, $constraint) {
  $sub_form['blacklist_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blacklist'),
  );
  $sub_form['blacklist_fieldset']['blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('Blacklisted passwords'),
    '#default_value' => $constraint->config['blacklist'],
    '#description' => t('Password cannot be a member of this list, ignoring case.  Enter one password per line.'),
  );

  return $sub_form;
}

/**
 * Constraint callback for blacklist constraint.
 */
function password_policy_blacklist_constraint($password, $account, $constraint) {
  $blacklist = explode("\n", $constraint->config['blacklist']);
  $blacklist = array_map('trim', $blacklist);
  $blacklist = array_filter($blacklist, 'strlen');

  foreach ($blacklist as $blacklisted_password) {
    if (strcasecmp($password, $blacklisted_password) == 0) {
      return FALSE;
    }
  }

  return TRUE;
}
