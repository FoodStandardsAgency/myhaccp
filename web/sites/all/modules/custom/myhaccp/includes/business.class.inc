<?php

/**
 * @file
 * Methods to help with businesses.
 */

/**
 * Class Business.
 */
class Business {

  /**
   * Setter function to store the user.
   *
   * @param object $user
   *   The user object.
   */
  public function setUser($user) {
    $this->user = $user;
  }

  /**
   * Getter function to return the user.
   *
   * @return object
   *   The stored user object or the global user if not stored.
   */
  public function getUser() {
    if (isset($this->user)) {
      return $this->user;
    }
    global $user;
    return $user;
  }

  /**
   * Setter function to store the business name.
   *
   * @param string $name
   *   A business name string.
   */
  protected function setBusinessName($name) {
    $this->business_name = $name;
  }

  /**
   * Getter function to return the business name.
   *
   * @return string
   *   The business name string.
   */
  public function getBusinessName() {
    // If we already have it then return it.
    if (isset($this->business_name)) {
      return $this->business_name;
    }
    // Fetch the business name from the user profile.
    $profile = $this->getUserProfile();
    // Its possible the user might not have a profile (edge case) so check
    // for an empty array and set an empty string.
    $business_name = !empty($profile) ? $this->getBusinessNameFromProfile($profile) : '';
    // Set the name so we can return it quicker if needed again.
    $this->setBusinessName($business_name);
    return $business_name;
  }

  /**
   * Local method for fetching a user profile from a user object.
   *
   * @return array|bool|mixed
   */
  protected function getUserProfile() {
    $profile = profile2_load_by_user($this->user->uid);
    return isset($profile['main']) ? $profile['main'] : array();
  }

  /**
   * Returns a business name given a user profile.
   *
   * @param object $profile
   *   A user profile object.
   *
   * @return string
   *   A business name string. Can also be an empty string.
   */
  protected function getBusinessNameFromProfile($profile) {
    $wrapper = entity_metadata_wrapper('profile2', $profile);
    $business_name = isset($wrapper->field_business_name) ? $wrapper->field_business_name->value() : '';
    return $business_name;
  }

  /**
   * Gets all the studies this user has.
   */
  public function getAllStudies() {
    $user = $this->getUser();
    return $this->getStudies($user);
  }

  /**
   * Retrieves studies for a given user.
   */
  protected function getStudies($user) {
    $studies = db_select('mforms_storage', 'ms')
      ->fields('ms', array('iid', 'uid'))
      ->condition('ms.uid', $user->uid)
      ->orderBy('ms.created', 'DESC')
      ->execute()
      ->fetchAllKeyed(0, 1);
    return $studies;
  }

  /**
   * Returns a list of studies for a user as an options array.
   */
  public function getStudiesOptionsArray($user) {
    $studies = $this->getStudies($user);
    $options = array();
    foreach ($studies as $iid => $uid) {
      $study = new Study();
      $study->setIID($iid);
      myhaccp_initialise_study($study);
      $options[$iid] = $study->getName();
    }
    return $options;
  }

}