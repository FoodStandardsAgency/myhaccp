<?php

define('NOT_STARTED', 0);
define('INVALID', 1);
define('VALID', 2);

class Configuration {

  /**
   * Returns an array keyed with the stage machine name (file name).
   *
   * @return array
   *   The key is the machine name of the stage, which is also used to construct
   *   the file name. The value is the phase the stage belongs to.
   */
  public function getFiles() {
    return $this->getMachineNames();
  }

  public function getMachineNames() {
    $names = array(
      'preparatory_intro' => 'preparatory',
      'preparatory_a' => 'preparatory',
      'preparatory_b' => 'preparatory',
      'preparatory_c_1' => 'preparatory',
      'preparatory_c_2' => 'preparatory',
      'preparatory_d' => 'preparatory',
      'preparatory_e' => 'preparatory',
      'preparatory_f' => 'preparatory',
      'preparatory_g' => 'preparatory',
      'preparatory_h' => 'preparatory',
      'preparatory_review' => 'preparatory',
      'principle_intro' => 'principle',
      'principle_1_1' => 'principle',
      'principle_1_2' => 'principle',
      'principle_1_3' => 'principle',
      'principle_2_1' => 'principle',
      'principle_2_2' => 'principle',
      'principle_3' => 'principle',
      'principle_4' => 'principle',
      'principle_5' => 'principle',
      'principle_6' => 'principle',
      'principle_7' => 'principle',
      'principle_review' => 'principle',
    );
    return $names;
  }

  public function getStageUrls() {
    return array(
      'preparatory_intro' => 'preparatory/introduction',
      'preparatory_a' => 'preparatory/a',
      'preparatory_b' => 'preparatory/b',
      'preparatory_c_1' => 'preparatory/c-1',
      'preparatory_c_2' => 'preparatory/c-2',
      'preparatory_d' => 'preparatory/d',
      'preparatory_e' => 'preparatory/e',
      'preparatory_f' => 'preparatory/f',
      'preparatory_g' => 'preparatory/g',
      'preparatory_h' => 'preparatory/h',
      'preparatory_review' => 'preparatory/review',
      'principle_intro' => 'principle/introduction',
      'principle_1_1' => 'principle/1-1',
      'principle_1_2' => 'principle/1-2',
      'principle_1_3' => 'principle/1-3',
      'principle_2_1' => 'principle/2-1',
      'principle_2_2' => 'principle/2-2',
      'principle_3' => 'principle/3',
      'principle_4' => 'principle/4',
      'principle_5' => 'principle/5',
      'principle_6' => 'principle/6',
      'principle_7' => 'principle/7',
      'principle_review' => 'principle/review',
    );
  }

  public function getStageTitles() {
    return array(
      'preparatory_intro' => 'Preparatory: Intro',
      'preparatory_a' => 'Preparatory Stage A: Prerequisites',
      'preparatory_b' => 'Preparatory Stage B: Obtain Management Commitment',
      'preparatory_c_1' => 'Preparatory Stage C: Define scope of the study',
      'preparatory_c_2' => 'Preparatory Stage C: Define scope of the study (Continued)',
      'preparatory_d' => 'Preparatory Stage D: Select the HACCP team',
      'preparatory_e' => 'Preparatory Stage E: Describe the product',
      'preparatory_f' => 'Preparatory Stage F: Identify intended use of the product',
      'preparatory_g' => 'Preparatory Stage G: Construct a flow diagram',
      'preparatory_h' => 'Preparatory Stage H: On-site confirmation of flow diagram',
      'preparatory_review' => 'Preparatory: Review',
      'principle_intro' => 'Principles: Intro',
      'principle_1_1' => 'Principle 1.1: Identify and list Potential Hazards',
      'principle_1_2' => 'Principle 1.2: Conduct a Hazard Analysis',
      'principle_1_3' => 'Principle 1.3: Specify the Control Measures for each hazard',
      'principle_2_1' => 'Principle 2.1: Determine the Critical Control Points (CCPs)',
      'principle_2_2' => 'Principle 2.2: Determine the Critical Control Points (CCPs) (Continued)',
      'principle_3' => 'Principle 3: Establish the Critical Limits',
      'principle_4' => 'Principle 4: Establish a Monitoring System for each CCP',
      'principle_5' => 'Principle 5: Establish a Corrective Action plan',
      'principle_6' => 'Principle 6: Verification',
      'principle_7' => 'Principle 7: Establish Documentation and Record Keeping',
      'principle_review' => 'Principles: Review',
    );
  }
}
