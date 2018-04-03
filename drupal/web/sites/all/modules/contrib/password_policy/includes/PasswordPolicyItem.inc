<?php
/**
 * @file
 * Contains PasswordPolicyItem.
 */

/**
 * Class PasswordPolicyItem
 *
 * This class is used for item CTools plugin type.
 */
class PasswordPolicyItem {
  protected $pp_type = array('item');
  public $info;
  public $policy;
  public $config;

  public function __construct($info, &$policy) {
    $this->info = $info;
    // We want to have a local config but have it be a ref to the policy one
    // that way we only have to make updates once.
    $this->config = &$policy->config[$info['name']];
    $this->config = array_merge($info['config'], $this->config);
    $this->policy = $policy;
  }

  public function is_type($type) {
    return in_array($type, $this->pp_type);
  }

  protected function func($function_name) {
    return ctools_plugin_get_function($this->info, $function_name);
  }

  public function admin_form($form, &$form_state) {
    if ($func = $this->func('admin form callback')) {
      return $func($form, $form_state, $this);
    }
    return array();
  }

  public function admin_form_submit($form, &$form_state) {
    foreach ($this->info['config'] as $id => $default) {
      if (isset($form_state['values'][$id])) {
        $this->config[$id] = $form_state['values'][$id];
      }
    }
  }

  // See if the constraint is active.
  public function is_active() {
    if (isset($this->info['prime value'])) {
      return (bool) $this->config[$this->info['prime value']];
    }
    else {
      return TRUE;
    }
  }

  public static function factory($info, &$policy) {
    $class = $info['class'];
    return new $class($info, $policy);
  }

}
