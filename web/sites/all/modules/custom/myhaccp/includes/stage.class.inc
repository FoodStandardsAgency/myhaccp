<?php


interface StageInterface {

  public function getPhase();

  public function setPhase(Phase $phase);

}

class Stage implements StageInterface {

  /**
   * Gets the phase this stage belongs to.
   */
  public function getPhase() {
    return $this->phase;
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
   * Gets the stage url.
   *
   * @return string
   *   The stage url.
   */
  public function getUrl() {
    return $this->url;
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
   * Gets the stage title.
   *
   * @return string
   *   The stage title.
   */
  public function getTitle() {
    return $this->title;
  }


}
