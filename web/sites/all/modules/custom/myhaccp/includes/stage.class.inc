<?php


interface StageInterface {

  public function getName();

  public function setName($name);

  public function getPhase();

  public function setPhase(Phase $phase);

  public function getStatus();

  public function setStatus($status);

  public function getValidator();

  public function setValidator(Validator $validator);

  public function getUrl();

  public function setUrl($url);

  public function getTitle();

  public function setTitle($title);

  public function getIID();

  public function setIID($iid);


}

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
    return $this->iid;
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

}
