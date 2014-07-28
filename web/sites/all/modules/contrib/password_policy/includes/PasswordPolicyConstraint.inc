<?php
/**
 * @file
 * Contains PasswordPolicyConstraint.
 */

/**
 * Class PasswordPolicyConstraint
 *
 * This class is to test individual policy constraints.
 */
class PasswordPolicyConstraint extends PasswordPolicyItem {
  protected $pp_type = array('item', 'constraint');

  public function message() {
    $mes_temp = is_array($this->info['message']) ? $this->info['message'] : array($this->info['message']);
    $messages = array();
    foreach ($mes_temp as $id => $message) {
      // Only show messages for constraints that have been configured.
      if ($this->config != $this->info['config']) {
        $args = array();
        foreach ($this->config as $key => $value) {
          $args['@' . $key] = $value;
        }
        $messages[$id] = format_string($message, $args);
      }
    }
    return $messages;
  }

  public function fail_message($password, $account) {
    return $this->message();
  }

  public function __construct($info, &$policy) {
    if (isset($info['default'])) {
      $info['prime value'] = $info['name'];
      $info['config'] = array($info['name'] => $info['default']);
    }
    parent::__construct($info, $policy);
  }

  public function check($pass, $account) {
    if ($func = $this->func('constraint callback')) {
      return $func($pass, $account, $this);
    }
  }
}
