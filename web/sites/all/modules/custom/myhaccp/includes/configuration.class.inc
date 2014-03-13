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

  public function getHelpPages() {
    return array(
      'preparatory_a' => 13,
      'preparatory_b' => 14,
      'preparatory_c_1' => 15,
      'preparatory_d' => 21,
      'preparatory_e' => 18,
      'preparatory_f' => 19,
      'preparatory_g' => 20,
      'preparatory_h' => 22,
      'principle_1_1' => 16,
      'principle_1_2' => 17,
      'principle_1_3' => 27,
      'principle_2_1' => 28,
      'principle_3' => 29,
      'principle_4' => 30,
      'principle_5' => 31,
      'principle_6' => 32,
      'principle_7' => 33,
    );
  }

  public function getPDFSections() {
    return array(
      '01_management' => array(
        'title' => 'Management commitment',
        'validation' => array(
          'preparatory_b',
        ),
        'theme' => array(
          'preparatory_b',
        ),
      ),
      '02_terms' => array(
        'title' => 'Terms of reference',
        'validation' => array(
          'preparatory_c_1',
          'preparatory_c_2',
          'preparatory_a',
        ),
        'theme' => array(
          'preparatory_c_1',
          'preparatory_c_2',
        ),
        'orientation' => 'P',
      ),
      '03_team' => array(
        'title' => 'The HACCP team',
        'validation' => array(
          'preparatory_d',
        ),
        'theme' => array(
          'preparatory_d',
        ),
        'orientation' => 'P',
      ),
      '04_product' => array(
        'title' => 'Product description and intended use',
        'validation' => array(
          'preparatory_e',
          'preparatory_f',
        ),
        'theme' => array(
          'preparatory_e',
          'preparatory_f',
        ),
        'orientation' => 'P',
      ),
      '05_process' => array(
        'title' => 'Process flow and confirmation',
        'validation' => array(
          'preparatory_g',
          'preparatory_h',
        ),
        'theme' => array(
          'preparatory_g',
          'preparatory_h',
        ),
        'orientation' => 'P',
      ),
      '06_identify' => array(
        'title' => 'Identify and list potential hazards',
        'validation' => array(
          'principle_1_1',
        ),
        'theme' => array(
          'principle_1_1',
        ),
        'orientation' => 'L',
      ),
      '07_severity' => array(
        'title' => 'Severity scores',
        'validation' => array(
          'principle_1_2',
        ),
        'theme' => array(
          'principle_1_2',
        ),
        'orientation' => 'L',
      ),
      '08_control' => array(
        'title' => 'Control Measures',
        'validation' => array(
          'principle_1_3',
        ),
        'theme' => array(
          'principle_1_3',
        ),
        'orientation' => 'L',
      ),
      '09_ccps' => array(
        'title' => 'CCPs for significant hazards',
        'validation' => array(
          'principle_2_1',
          'principle_2_2',
        ),
        'theme' => array(
          'principle_2_1',
          'principle_2_2',
        ),
        'orientation' => 'L',
      ),
      '10_critical' => array(
        'title' => 'Critical limits for the CCPs',
        'validation' => array(
          'principle_3',
        ),
        'theme' => array(
          'principle_3',
        ),
        'orientation' => 'L',
      ),
      '11_plan' => array(
        'title' => 'The HACCP Plan',
        'validation' => array(
          'principle_3',
          'principle_4',
          'principle_5',
        ),
        'theme' => array(
          'principle_3',
          'principle_4',
          'principle_5',
        ),
        'orientation' => 'L',
      ),
      '12_verification' => array(
        'title' => 'Verification',
        'validation' => array(
          'principle_6',
        ),
        'theme' => array(
          'principle_6',
        ),
        'orientation' => 'P',
      ),
      '13_documentation' => array(
        'title' => 'Documentation and record keeping',
        'validation' => array(
          'principle_7',
        ),
        'theme' => array(
          'principle_7',
        ),
        'orientation' => 'P',
      ),
    );
    // Determine the orientation of the pages and where page breaks occur.
//    $breaks = array(
//      'preparatory_c_1' => 'P',
//      'preparatory_d' => 'P',
//      'preparatory_e' => 'P',
//      'preparatory_g' => 'P',
//      'principle_1_1' => 'L',
//      'principle_1_2' => 'L',
//      'principle_1_3' => 'L',
//      'principle_2_1' => 'L',
//      'principle_3' => 'L',
//      'principle_5' => 'L',
//      'principle_6' => 'P',
//      'principle_7' => 'P',
//    );
  }
}
