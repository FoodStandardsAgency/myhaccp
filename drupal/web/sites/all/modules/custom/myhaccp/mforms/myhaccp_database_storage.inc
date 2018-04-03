<?php

/**
 * @file
 * Storage class for mforms.
 *
 * Writes the form_state to the database for persistent storage.
 */

/**
 * Implementation of MformsIstore.
 */
class MformsDatabaseStore implements MformsIstore {

  protected $store_key;
  protected $form_state;
  private static $instance;

  /**
   * Gets an instance based on store key.
   *
   * @param string $store_key
   *
   * @return MformsIstore
   */
  static function getInstance($store_key) {
    if (self::$instance == NULL || self::$instance->getKey() != $store_key) {
      $class = get_called_class();

      self::$instance = new $class($store_key);
    }
    return self::$instance;
  }

  /**
   * Inits the store object.
   *
   * @param string $store_key
   *   Store key.
   */
  protected function __construct($store_key) {
    $this->store_key = $store_key;
    $this->iid = $_SESSION['iid'];
  }

  /**
   * Returns the store_key.
   */
  public function getKey() {
    return $this->store_key;
  }

  /**
   * Writes the store to the database.
   */
  public function setStore($key, $data) {
    // As a safety measure we only allow storage of data which has the key in
    // it. That means that the form element needs to be named the same as the
    // key (function name). For instance: $form['preparatory_a'][...]
    if (strpos($key, 'preparatory') !== FALSE || strpos($key, 'principle') !== FALSE) {
      if (!isset($data[$key])) {
        return;
      }
    }

    // Determine whether there is an existing record for this combination of
    // key and iid.
    $sid = db_select('mforms_storage_steps', 's')
      ->fields('s', array('sid'))
      ->condition('s.store_key', $key)
      ->condition('s.iid', $this->iid)
      ->execute()->fetchField();
    $record = array(
      'sid' => $sid,
      'iid' => $this->iid,
      'store_key' => $key,
      'store_data' => serialize($data),
    );
    if ($sid) {
      // There is an existing record so update it.
      drupal_write_record('mforms_storage_steps', $record, 'sid');
    }
    else {
      // This is a new record.
      drupal_write_record('mforms_storage_steps', $record);
    }
    // Finally update the timestamp for the changed field on the parent row.
    $record = array(
      'iid' => $this->iid,
      'changed' => time(),
    );
    drupal_write_record('mforms_storage', $record, 'iid');
  }

  /**
   * Gets the stored record for the given key.
   */
  public function getStore($key) {
    global $_myhaccp_container;
    $study = $_myhaccp_container['study'];
    $configuration = $_myhaccp_container['configuration'];

    // The step names (functions) are only stored in the db once submitted but
    // we want to be able to jump around between steps so need them declared
    // up front.
    if ($key == 'steps') {
      return array_keys($configuration->getMachineNames());
    }

    // Check if there is a specified stage url.
    if ($key == 'curr_step' && arg(3) && arg(4)) {
      $url = $_GET['q'];
      $parts = explode('/', $url);
      // Match the url to a stage function.
      if (isset($parts[3]) && isset($parts[4]) && $study->getPhase($parts[3])) {
        if ($stage = $study->getStageFromUrl(arg(3), arg(4))) {
          $study->setCurrentStage($stage);
          return $stage->name;
        }
      }
    }

    // Load the results from the db.
    $data = db_select('mforms_storage', 'm');
    $data->join('mforms_storage_steps', 's', 's.iid = m.iid');
    $data->fields('s', array('store_data'))
      ->condition('m.iid', $this->iid)
      ->condition('s.store_key', $key);
    $result = $data->execute()->fetchField();
    if ($result) {
      $data = unserialize($result);
      return $data;
    }
    return NULL;
  }

  /**
   * Clears the store key from the session variable.
   */
  function clearStore() {
    $_SESSION[$this->store_key] = NULL;
  }

  /**
   * Sets the form state.
   */
  function setFormState(array &$form_state) {
    $this->form_state = $form_state;
  }

  /**
   * Gets the form state.
   */
  function getFormState() {
    return $this->form_state;
  }
}
