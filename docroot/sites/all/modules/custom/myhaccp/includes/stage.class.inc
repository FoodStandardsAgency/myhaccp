<?php

/**
 * @file
 * Handles the stages.
 */

/**
 * Interface StageInterface.
 */
interface StageInterface {

  /**
   * Gets this stage's machine name.
   *
   * @return string
   *   The machine name of the stage.
   */
  public function getName();

  /**
   * Sets the machine name of the stage.
   *
   * @param string $name
   *   The machine name of the stage.
   */
  public function setName($name);

  /**
   * Gets the phase this stage belongs to.
   */
  public function getPhase();

  /**
   * Sets the phase this stage belongs to.
   *
   * @param Phase $phase
   *   An instance of the Phase object.
   */
  public function setPhase(Phase $phase);

  /**
   * A stage is in one of three states.
   *
   * @return int
   *   The state the stage is in.
   */
  public function getStatus();

  /**
   * Sets the state of the stage.
   *
   * @param int $status
   *   The status as an integer.
   */
  public function setStatus($status);

  /**
   * Gets the validator service for this stage.
   */
  public function getValidator();

  /**
   * Sets the validator service object.
   *
   * @param Validator $validator
   *   The validator service.
   */
  public function setValidator(Validator $validator);

  /**
   * Gets the stage url.
   *
   * @return string
   *   The stage url.
   */
  public function getUrl();

  /**
   * Sets the stage url.
   *
   * @param string $url
   *   The url for the stage.
   */
  public function setUrl($url);

  /**
   * Gets the stage title.
   *
   * @return string
   *   The stage title.
   */
  public function getTitle();

  /**
   * Sets the stage title.
   *
   * @param string $title
   *   The url for the stage.
   */
  public function setTitle($title);

  /**
   * Gets the study's IID.
   *
   * @return int
   *   The IID of the study.
   */
  public function getIID();

  /**
   * Sets the IID of the study.
   *
   * @param int $iid
   *   The IID of the study.
   */
  public function setIID($iid);

}

/**
 * Class Stage.
 */
class Stage implements StageInterface {

  /**
   * Gets this stage's machine name.
   *
   * @return string
   *   The machine name of the stage.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Sets the machine name of the stage.
   *
   * @param string $name
   *   The machine name of the stage.
   */
  public function setName($name) {
    $this->name = $name;
  }

  /**
   * Sets the IID of the study.
   *
   * @param int $iid
   *   The IID of the study.
   */
  public function setIID($iid) {
    $this->iid = $iid;
  }

  /**
   * Gets the study's IID.
   *
   * @return int
   *   The IID of the study.
   */
  public function getIID() {
    if (isset($this->iid)) {
      return $this->iid;
    }
  }

  /**
   * Gets the phase this stage belongs to.
   */
  public function getPhase() {
    if (isset($this->phase)) {
      return $this->phase;
    }
  }

  /**
   * Sets the phase this stage belongs to.
   *
   * @param Phase $phase
   *   An instance of the Phase object.
   */
  public function setPhase(Phase $phase) {
    $this->phase = $phase;
  }

  /**
   * A stage is in one of three states.
   *
   * @return int
   *   The state the stage is in.
   */
  public function getStatus() {
    if (isset($this->status)) {
      return $this->status;
    }
    else {
      $status = $this->getValidator()->getStatus(TRUE);
      $this->setStatus($status);
      return $this->getStatus();
    }
  }

  /**
   * Sets the state of the stage.
   *
   * @param int $status
   *   The status as an integer.
   */
  public function setStatus($status) {
    $this->status = $status;
  }

  /**
   * Gets the validator service for this stage.
   */
  public function getValidator() {
    return $this->validator;
  }

  /**
   * Sets the validator service object.
   *
   * @param Validator $validator
   *   The validator service.
   */
  public function setValidator(Validator $validator) {
    $this->validator = $validator;
    $this->validator->setStage($this);
    $this->validator->setIID($this->getIID());
  }

  /**
   * Gets the stage url.
   *
   * @return string
   *   The stage url.
   */
  public function getUrl() {
    return $this->url;
  }

  /**
   * Sets the stage url.
   *
   * @param string $url
   *   The url for the stage.
   */
  public function setUrl($url) {
    $this->url = $url;
  }

  /**
   * Gets the stage title.
   *
   * @return string
   *   The stage title.
   */
  public function getTitle() {
    return $this->title;
  }

  /**
   * Sets the stage title.
   *
   * @param string $title
   *   The url for the stage.
   */
  public function setTitle($title) {
    $this->title = $title;
  }

  /**
   * Fetches the stage data from the database.
   *
   * @return array|bool
   *   The data for the stage from the database or FALSE if not found.
   */
  public function getData() {
    $query = db_select('mforms_storage', 'm');
    $query->join('mforms_storage_steps', 's', 's.iid = m.iid');
    $query->fields('s', array('store_data'))
      ->condition('m.iid', $this->getIID())
      ->condition('s.store_key', $this->getName());
    $result = $query->execute()->fetchField();
    if ($result) {
      return (unserialize($result));
    }
    return FALSE;
  }

}
