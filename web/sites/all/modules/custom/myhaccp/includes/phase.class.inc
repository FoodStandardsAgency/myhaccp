<?php

/**
 * @file
 * Handles phases of the form.
 */

interface PhaseInterface {

  public function getName();

  public function setName($name);

  public function getStudy();

  public function setStudy(Study $study);

}

class Phase implements PhaseInterface {

  /**
   * Gets this phase's machine name.
   *
   * @return string
   *   The machine name of the phase.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Sets the machine name of the phase.
   *
   * @param string $name
   *   The machine name of the phase.
   */
  public function setName($name) {
    $this->name = $name;
  }

  /**
   * Gets the study this phase belongs to.
   */
  public function getStudy() {
    return $this->study;
  }

  /**
   * Sets the study this phase belongs to.
   *
   * @param Study $study
   *   An instance of the Study object.
   */
  public function setStudy(Study $study) {
    $this->study = $study;
  }

  /**
   * Adds a stage to an array of stages.
   *
   * @param Stage $stage
   *   The stage object to add to the phase.
   */
  public function addStage(Stage $stage) {
    $this->stages[$stage->getName()] = $stage;
  }

  /**
   * Returns a stage.
   *
   * @param string $stage
   *   The machine name of the stage.
   *
   * @return Stage
   *   The stage object.
   */
  public function getStage($stage) {
    return $this->stages[$stage];
  }

  /**
   * Returns an array of stages in this phase.
   *
   * @return array
   *   All the stages in this phase.
   */
  public function getStages() {
    return $this->stages;
  }

}
