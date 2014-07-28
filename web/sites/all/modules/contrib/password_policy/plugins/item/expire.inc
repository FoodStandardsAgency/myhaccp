<?php
/**
 * @file
 * Expiration plugin for Password Policy module.
 */

$plugin = array(
  'admin form callback' => 'password_policy_expire_admin_form',
  'prime value' => 'expire_limit',
  'class' => 'PasswordPolicyExpire',
  'config' => array(
    'expire_limit' => 0,
    'expire_warning_message' => 'Your Password has expired please change it now',
    'expire_warning_email_sent' => "-14 days",
    'expire_warning_email_message' => '',
    'expire_warning_email_subject' => '[user:name] you password on [site:name] ([site:url]) is going to expire on [password_expiration_date:long] please login and change it ([user:edit-url]) before then.',
    'expire_warning_email_subject' => '[user:name] you password on [site:name] shall expire in [password_expiration_date:interval] ',
  ),
);

/**
 * Admin form callback for expiration plugin.
 */
function password_policy_expire_admin_form($form, &$form_state, $constraint) {
  $sub_form['expire_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => 'Password expiration',
    '#collapsible' => TRUE,
    '#collapsed' => !(bool) $constraint->config['expire_limit'],
  );
  $sub_form['expire_fieldset']['expire_limit'] = array(
    '#type' => 'textfield',
    '#title' => 'Expire limit',
    '#default_value' => $constraint->config['expire_limit'],
    '#description' => "Password will expire after being used for this long (use normal English, like 90 days or 5 hours)",
  );
  $sub_form['expire_fieldset']['expire_warning_message'] = array(
    '#type' => 'textfield',
    '#title' => 'Warning message',
    '#default_value' => $constraint->config['expire_warning_message'],
    '#description' => t('A message to show to users on screen when requiring them to change password. <strong>If left empty, no message will be shown.</strong>'),
  );
  $sub_form['expire_fieldset']['expire_warning_email_sent'] = array(
    '#type' => 'textfield',
    '#title' => 'When to send warning emails',
    '#default_value' => $constraint->config['expire_warning_email_sent'],
    '#description' => t('A comma separated list of time intervals, when to send warning emails. (Use normal English, like 90 days or 5 hours).  If prefixed with a negative (like -2 days) then this will be before the expiration. If left empty, no email will be sent.'),
  );
  $sub_form['expire_fieldset']['expire_warning_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => 'Warning subject',
    '#default_value' => $constraint->config['expire_warning_email_subject'],
    '#description' => t(''),
    '#states' => array(
      'visible' => array(
        ':input[name="expire_warning_email_sent"]' => array('empty' => FALSE),
      ),
    ),
  );
  $sub_form['expire_fieldset']['expire_warning_email_message'] = array(
    '#type' => 'textarea',
    '#title' => 'Warning message',
    '#default_value' => $constraint->config['expire_warning_email_message'],
    '#description' => t(''),
    '#states' => array(
      'visible' => array(
        ':input[name="expire_warning_email_sent"]' => array('empty' => FALSE),
      ),
    ),
  );
  $sub_form['expire_fieldset']['expire_warning_email_message_token'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('user', 'site', 'current-date', 'password_expiration_date'),
    '#global_types' => FALSE,
    '#click_insert' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="expire_warning_email_sent"]' => array('empty' => FALSE),
      ),
    ),
  );
  return $sub_form;
}

function _password_policy_expire_notify($account, $candidate, $expire, $item) {
  $body = token_replace($item->config['expire_warning_email_message'], array(
    'user' => $account,
    'password_expiration_date' => $expire,
  ));
  $subject = token_replace($item->config['expire_warning_email_subject'], array(
    'user' => $account,
    'password_expiration_date' => $expire,
  ));
  $message = drupal_mail('password_policy', 'warning', $account->mail, user_preferred_language($account), array('body' => $body, 'subject' => $subject));

  return $message;
}

function _password_policy_expire_query_users($notice_int, $policy_name) {
  $current_pw_query = db_select('password_policy_history', 'c');
  $current_pw_query
    ->fields('c', array('uid'))
    ->groupBy('uid')
    ->addExpression('MAX(created)', 'created');

  $query = db_select('password_policy_history', 'p');

  $query->fields('p', array('uid', 'hid', 'created'));

  // Join to our active password so we are only looking at the most recent.
  $query->join($current_pw_query, 'c', 'p.created = c.created AND p.uid = c.uid');

  // Add negative join to remove all items that have already sent this notice.
  // @TODO findout why we cannot use arguments here
  // $query->leftJoin('password_policy_notice_history', 'nh', "nh.hid = p.hid AND nh.timeframe = '%s' AND nh.name='%s'", array($notice_int, $policy_name));
  $condition = t("nh.hid = p.hid AND nh.name='@name' AND nh.timeframe = '@timeframe'", array('@name' => $policy_name, '@timeframe' => $notice_int));
  $query->leftJoin('password_policy_notice_history', 'nh', $condition);
  $query->isNull('nh.hid');

  // Check to see if the password needs a warning notification.
  $query->condition('p.created', time() - $notice_int, '<');

  // Package up the candidates and return them.
  $candidates = array();
  $result = $query->execute();
  foreach ($result as $row) {
    $candidates[$row->uid] = $row;
  }

  return $candidates;
}

class PasswordPolicyExpire extends PasswordPolicyItem {
  public $pp_type = array('item', 'cron', 'init');

  /**
   * Checks on init if the user password has expired. If so, we send the user
   * to the user edit page until they set a new password.
   */
  public function init($account) {
    // If this is a command line request (Drush, etc), skip processing.
    if (drupal_is_cli()) {
      return FALSE;
    }

    $stop = module_invoke_all('password_policy_expire_url_exclude', $account);
    if (!empty($stop)) {
      return FALSE;
    }

    // @TODO this should not be necessary
    password_policy_user_load(array($account->uid => $account));
    if ($account->uid == 0) {
      return;
    }
    $expire_int = password_policy_parse_interval($this->config['expire_limit']);
    if (!$expire_int) {
      return;
    }

    // If there is no password history, start one.
    if (!isset($account->password_history[0])) {
      $account->password_history[0] = (object) array(
        'uid' => $account->uid,
        'pass' => $account->pass,
        'created' => time()
      );
      password_policy_update_password_history($account->password_history[0]);
    }
    // Check to see that the password has expired.
    if ($account->password_history[0]->created + $expire_int < time()) {
      // If we are on the check ajax page, then skip.
      if ($_GET['q'] != 'password_policy/check') {
        $uri = "user/{$account->uid}/edit";

        // If not on the user page, go there, but remember where we were.
        if ($_GET['q'] != $uri) {
          // If we have been here before, we do not want to override this
          // info (it might be an ajax call).
          if (!isset($_SESSION['password_policy_lock'])) {
            $_SESSION['password_policy_lock'] = TRUE;
//            $_SESSION['password_policy_GET'] = $_GET;
//            $_SESSION['password_policy_POST'] = $_POST;
          }
          if (!empty($this->config['expire_warning_message'])) {
            drupal_set_message($this->config['expire_warning_message'], 'warning');
          }
          password_policy_goto($uri);
        }
        // If we are on the user edit screen, set the destination so we go back.
        else {
// Comment this out for now.  Causes infinite redirect loop when password expires
//          $_GET['destination'] = $_SESSION['password_policy_GET']['q'];
        }
      }
    }
    // Reset post and get if we are not locked.
    elseif (isset($_SESSION['password_policy_lock'])) {
//      $_GET = $_SESSION['password_policy_GET'];
//      $_POST = $_SESSION['password_policy_POST'];
      unset($_SESSION['password_policy_lock']);
    }
  }

  /**
   * Pulls all users that have expired passwords, insure they are active with
   * this policy, and then notify them of their soon-to-be expired password.
   */
  public function cron() {
    // Dont do anything if the policy does not require notification emails.
    if (empty($this->config['expire_warning_email_sent'])) {
      return;
    }

    $notice_interval_strings = explode(',', $this->config['expire_warning_email_sent']);
    $expire_interval_string = $this->config['expire_limit'];
    $policy_name = $this->policy->name;

    foreach ($notice_interval_strings as $notice_interval_string) {
      $notice_interval_string = trim($notice_interval_string);
      // See if we should be subtracting from expire interval.
      $from_interval = drupal_substr($notice_interval_string, 0, 1) == '-';
      $notice_interval_string = ltrim($notice_interval_string, '-');

      // Convert notice interval to secs.
      $notice_int = password_policy_parse_interval($notice_interval_string);

      // If we need to subtract from expire do so.
      $expire_interval = password_policy_parse_interval($expire_interval_string);
      $expire_int = password_policy_parse_interval($expire_interval_string);
      if ($from_interval) {
        $notice_int = $expire_int - $notice_int;
      }
      $candidates = _password_policy_expire_query_users($notice_int, $policy_name);
      foreach ($candidates as $candidate) {
        $account = user_load($candidate->uid);
        if ($this->policy->match($account)) {
          $message = _password_policy_expire_notify($account, $candidate, $candidate->created + $expire_int, $this);
          if ($message['result']) {
            watchdog('password_policy', 'Password expiration warning mailed to %username at %email.', array('%username' => $account->name, '%email' => $account->mail));
            $notice_history = (object) array(
              'hid' => $candidate->hid,
              'name' => $this->policy->name,
              'timeframe' => $notice_int,
              'sent' => time(),
            );
            drupal_write_record('password_policy_notice_history', $notice_history);
          }
        }
      }
    }
  }

}
