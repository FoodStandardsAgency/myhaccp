<?php

/**
 * @file
 * A configuration class with definitions for various options.
 *
 * This class is called by various other classes and is used to provide
 * defined configuration in the form of keyed arrays.
 */

define('NOT_STARTED', 0);
define('INVALID', 1);
define('VALID', 2);

/**
 * Class Configuration.
 */
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

  /**
   * Relates stages with phases.
   *
   * @return array
   *   An array keyed by the stage machine name with the value representing
   *   the phase the stage belongs to.
   */
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

  /**
   * Relates stage machine names to urls.
   *
   * @return array
   *   An array keyed by stage machine name with the value representing the
   *   url the stage can be found at.
   */
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

  /**
   * Relates stage machine names to stage titles.
   *
   * @return array
   *   An array keyed by stage machine name with the value representing the
   *   stage title.
   */
  public function getStageTitles() {
    return array(
      'preparatory_intro' => t('Preparatory: Introduction'),
      'preparatory_a' => t('Preparatory Stage A: Prerequisites'),
      'preparatory_b' => t('Preparatory Stage B: Obtain Management Commitment'),
      'preparatory_c_1' => t('Preparatory Stage C: Define scope of the study'),
      'preparatory_c_2' => t('Preparatory Stage C: Define scope of the study (Continued)'),
      'preparatory_d' => t('Preparatory Stage D: Select the HACCP team'),
      'preparatory_e' => t('Preparatory Stage E: Describe the product'),
      'preparatory_f' => t('Preparatory Stage F: Identify intended use of the product'),
      'preparatory_g' => t('Preparatory Stage G: Construct a flow diagram'),
      'preparatory_h' => t('Preparatory Stage H: On-site confirmation of flow diagram'),
      'preparatory_review' => t('Preparatory: Review'),
      'principle_intro' => t('Principles: Introduction'),
      'principle_1_1' => t('Principle 1.1: Identify and list Potential Hazards'),
      'principle_1_2' => t('Principle 1.2: Conduct a Hazard Analysis'),
      'principle_1_3' => t('Principle 1.3: Specify the Control Measures for each hazard'),
      'principle_2_1' => t('Principle 2.1: Determine the Critical Control Points (CCPs)'),
      'principle_2_2' => t('Principle 2.2: Determine the Critical Control Points (CCPs) (Continued)'),
      'principle_3' => t('Principle 3: Establish the Critical Limits'),
      'principle_4' => t('Principle 4: Establish a Monitoring System for each CCP'),
      'principle_5' => t('Principle 5: Establish a Corrective Action plan'),
      'principle_6' => t('Principle 6: Verification'),
      'principle_7' => t('Principle 7: Establish Documentation and Record Keeping'),
      'principle_review' => t('Principles: Review'),
    );
  }

  /**
   * Relates stage machine names to help node IDs.
   *
   * @return array
   *   An array keyed by stage machine name with the value representing the
   *   node ID of the related help page.
   */
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

  /**
   * Returns configuration for the PDF section output.
   *
   * @return array
   *   An array keyed by the PDF section machine name with sub elements
   *   representing the title, which validation needs to pass for the section
   *   to be shown and which theme function is used to provide the output
   *   variables for the template file.
   */
  public function getPDFSections() {
    return array(
      '01_management' => array(
        'title' => t('Management commitment'),
        'validation' => array(
          'preparatory_b',
        ),
        'theme' => array(
          'preparatory_b',
        ),
      ),
      '02_terms' => array(
        'title' => t('Terms of reference'),
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
        'title' => t('The HACCP team'),
        'validation' => array(
          'preparatory_d',
        ),
        'theme' => array(
          'preparatory_d',
        ),
        'orientation' => 'P',
      ),
      '04_product' => array(
        'title' => t('Product description and intended use'),
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
        'title' => t('Process flow and confirmation'),
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
        'title' => t('Identify and list potential hazards'),
        'validation' => array(
          'principle_1_1',
        ),
        'theme' => array(
          'principle_1_1',
        ),
        'orientation' => 'L',
      ),
      '07_severity' => array(
        'title' => t('Severity scores'),
        'validation' => array(
          'principle_1_2',
        ),
        'theme' => array(
          'principle_1_2',
        ),
        'orientation' => 'L',
      ),
      '08_control' => array(
        'title' => t('Control Measures'),
        'validation' => array(
          'principle_1_3',
        ),
        'theme' => array(
          'principle_1_3',
        ),
        'orientation' => 'L',
      ),
      '09_ccps' => array(
        'title' => t('CCPs for significant hazards'),
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
        'title' => t('Critical limits for the CCPs'),
        'validation' => array(
          'principle_3',
        ),
        'theme' => array(
          'principle_3',
        ),
        'orientation' => 'L',
      ),
      '11_plan' => array(
        'title' => t('The HACCP Plan'),
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
        'title' => t('Verification'),
        'validation' => array(
          'principle_6',
        ),
        'theme' => array(
          'principle_6',
        ),
        'orientation' => 'P',
      ),
      '13_documentation' => array(
        'title' => t('Documentation and record keeping'),
        'validation' => array(
          'principle_7',
        ),
        'theme' => array(
          'principle_7',
        ),
        'orientation' => 'P',
      ),
      'appendix_a' => array(
        'type' => 'appendix',
        'title' => t('Appendix A - Flow Diagram'),
        'process_function' => 'process_appendix_a',
      ),
    );
  }

  /**
   * Sets PHPWord configuration.
   *
   * @param \PhpOffice\PhpWord\PhpWord $phpWord
   *   The PhpWord Class.
   */
  public function setPHPWordConfig($phpWord) {
    // Heading 1.
    $phpWord->addTitleStyle(1, array(
      'bold' => TRUE,
      'size' => 20,
    ), array(
      'spaceBefore' => \PhpOffice\PhpWord\Shared\Converter::inchToTwip(2.5),
      'spaceAfter' => \PhpOffice\PhpWord\Shared\Converter::inchToTwip(0.5),
    ));
    // Heading 2.
    $phpWord->addTitleStyle(2, array(
      'bold' => FALSE,
      'color' => '006F51',
      'name' => 'Arial',
      'size' => 20,
    ), array(
      'spaceAfter' => 240,
      'borderBottomColor' => 'dddddd',
      'borderBottomSize' => 25,
      'lineHeight' => 1.25,
    ));
    // Heading 3.
    $phpWord->addTitleStyle(3, array(
      'bold' => FALSE,
      'color' => '888888',
      'name' => 'Arial',
      'size' => 13,
    ), array(
      'spaceAfter' => 240,
      'line-height' => 1.5,
    ));
    // Heading 4.
    $phpWord->addTitleStyle(4, array(
      'bold' => FALSE,
      'color' => '888888',
      'name' => 'Arial',
      'size' => 11,
    ), array(
      'spaceAfter' => 240,
      'line-height' => 1.5,
    ));
    // Paragraph style.
    $phpWord->addParagraphStyle('ps', array(
      'spaceAfter' => 240,
      'line-height' => 1.5,
    ));
    // Paragraph style for lists.
    $phpWord->addParagraphStyle('ps-list', array(
      'spaceAfter' => 0,
      'line-height' => 1.25,
    ));
    $phpWord->setDefaultParagraphStyle(array(
      'spaceAfter' => 0,
      'line-height' => 1.25,
    ));
    $phpWord->setDefaultFontName('Arial');
    $phpWord->setDefaultFontSize(11);
    // Body copy style.
    $phpWord->addFontStyle('fs',
      array(
        'name' => 'Arial',
        'size' => 11,
        'color' => '000000',
      ),
      array(
        'spaceAfter' => 175,
        'line-height' => 1.5,
      )
    );
    $phpWord->addFontStyle('fs-list',
      array(
        'name' => 'Arial',
        'size' => 11,
        'color' => '000000',
      ),
      array(
        'spaceAfter' => 0,
        'line-height' => 1.25,
      )
    );
    $phpWord->addFontStyle('fs-theader',
      array(
        'name' => 'Arial',
        'size' => 11,
        'color' => '000000',
        'bold' => TRUE,
      ),
      array(
        'spaceAfter' => 0,
        'line-height' => 1.25,
      )
    );
    $phpWord->addTableStyle('ts',
      array(
        'borderSize' => 1,
        'borderColor' => 'DDDDDD',
        'cellMargin' => 80,
        'width' => 100 * 50,
        'unit' => 'pct',
      ),
      array(
        'bgColor' => 'EEEEEE',
      )
    );
  }

}
