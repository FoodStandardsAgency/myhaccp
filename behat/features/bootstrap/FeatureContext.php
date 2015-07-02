<?php

use Drupal\DrupalExtension\Context\DrupalContext,
    Drupal\DrupalExtension\Event\EntityEvent;

use Behat\Behat\Exception\PendingException,
    Behat\Behat\Context\Step;

use Behat\Mink\Selector;

use Behat\Gherkin\Node\PyStringNode,
    Behat\Gherkin\Node\TableNode;

use Behat\Mink\Exception\ElementNotFoundException;

require 'vendor/autoload.php';

class FeatureContext extends Drupal\DrupalExtension\Context\DrupalContext {

  /**
   * @Given /^I start a new study$/
   */
  public function iStartANewStudy() {
    return new Step\Given("I visit \"tools/study/create\"");
  }

  /**
   * @AfterSuite
   */
  public static function cleanDatabase($event) {
    // Get the highest (newest) uid from users table.
    $query = db_select('mforms_storage', 'm')
      ->fields('m', array('iid'))
      ->orderBy('m.iid', 'DESC')
      ->range(0, 1);
    $iid = $query->execute()->fetchField();
    // Remove all entries in the mforms_storage and mforms_storage_steps tables.
    if ($iid) {
      db_delete('mforms_storage')
        ->condition('iid', $iid)
        ->execute();

      // Delete all form state entries.
      if ($iid) {
        db_delete('mforms_storage_steps')
          ->condition('iid', $iid)
          ->execute();
      }
    }
  }

  /**
   * @When /^I complete principle "([^"]*)"$/
   */
  public function iCompletePrinciple($stage) {
    $function = 'principle_' . str_replace('.', '_', $stage);
    return $this->$function();
  }

  /**
   * @Given /^I complete all principles up to "([^"]*)"$/
   */
  public function iCompleteAllPrinciplesUpTo($stage) {
    $stages = $this->getPrinciples();
    $complete = array();
    // Iterate through each stage until we get to the stated stage.
    foreach ($stages as $name => $type) {
      $complete = array_merge($complete, $this->$name());
      $stage_name = 'principle_' . str_replace('.', '_', $stage);
      if ($stage_name == $name) {
        // Stop iterating.
        break;
      }
      // Add a save and continue as we have further stages.
      $complete[] = new Step\When('I press the "Save and continue" button');
    }
    return $complete;
  }

  /**
   * @When /^I fill in field "([^"]*)" with "([^"]*)"$/
   */
  public function iFillInFieldWith($field, $value) {
    // Try to get the field by css.
    $field = $this->fixStepArgument($field);
    $value = $this->fixStepArgument($value);
    $field = $this->getSession()->getPage()->find('css', $field);
    // Check if we found a field.
    if (null === $field) {
      throw new ElementNotFoundException(
        $this->getSession(), 'form field', 'css', $field
      );
    }
    $field->setValue($value);
  }

  /**
   * @When /^I fill row "([^"]*)" "([^"]*)" with "([^"]*)"$/
   */
  public function iFillRowWith($row, $class, $value) {
    $row = $this->fixStepArgument($row);
    $class = $this->fixStepArgument($class);
    $value = $this->fixStepArgument($value);
    // Get the field by row and class.
    $target = 'tr:nth-of-type(' . $row . ') td .' . $class;
    $field = $this->getSession()->getPage()->find('css', $target);
    // Check if we found a field.
    if (NULL === $field) {
      throw new ElementNotFoundException($this->getSession(), 'form field', 'css', $field);
    }
    // Set the field's value.
    $field->setValue($value);
  }

  /**
   * @When /^I select the radio button "([^"]*)" in row "([^"]*)" "([^"]*)"$/
   */
  public function iSelectTheRadioButtonInRow($label, $row, $class) {
    $row = $this->fixStepArgument($row);
    $class = $this->fixStepArgument($class);
    $label = $this->fixStepArgument($label);
    // Get the field by row and class.
    $target = 'tr:nth-of-type(' . $row . ') td .' . $class;
    $parent = $this->getSession()->getPage()->find('css', $target)->getParent();
    // Now find the right input field.
    $field = $parent->find('named', array(
      'radio',
      $this->getSession()->getSelectorsHandler()->xpathLiteral($label),
    ));
    if (NULL === $field) {
      throw new ElementNotFoundException($this->getSession(), 'form field', 'css', $field);
    }
    $value = $field->getAttribute('value');
    // Set the field's value.
    $field->setValue($value);
  }

  protected function principle_1_1() {
    return array(
      new Step\When('I fill in "Step no." with "1"'),
      new Step\When('I fill in "Step name" with "A step in my process"'),
      new Step\When('I fill in "Biological" with "Salmonella spp."'),
      new Step\When('I fill in "Allergens" with "Sesame seeds"'),
      new Step\When('I fill in "Physical" with "Stones"')
    );
  }

  protected function principle_1_2() {
    return array(
      new Step\When('I fill row "1" "description" with "A description"'),
      new Step\When('I fill row "1" "severity" with "3"'),
      new Step\When('I fill row "1" "likelihood" with "3"'),
      new Step\When('I fill row "1" "significance" with "9"'),
      new Step\When('I fill row "2" "description" with "Stones description"'),
      new Step\When('I fill row "2" "severity" with "3"'),
      new Step\When('I fill row "2" "likelihood" with "2"'),
      new Step\When('I fill row "2" "significance" with "6"'),
      new Step\When('I fill row "3" "description" with "Another description"'),
      new Step\When('I fill row "3" "severity" with "1"'),
      new Step\When('I fill row "3" "likelihood" with "2"'),
      new Step\When('I fill row "3" "significance" with "2"'),
      new Step\When('I fill in "Determine the threshold" with "5"'),
    );
  }

  protected function principle_1_3() {
    return array(
      new Step\When('I fill row "1" "control-measure" with "My control measure"'),
      new Step\When('I fill row "2" "control-measure" with "Another control measure"'),
    );
  }

  protected function principle_2_1() {
    return array(
      new Step\When('I select the radio button "Yes"'),
      new Step\When('I select "Campden" from "1a"'),
    );
  }

  protected function principle_2_2() {
    return array(
      new Step\When('I select the radio button "Yes" in row "1" "form-type-radios"'),
      new Step\When('I select the radio button "Yes" in row "2" "form-type-radios"'),
      new Step\When('I select the radio button "Yes" in row "1" "ccp"'),
      new Step\When('I select the radio button "Yes" in row "2" "ccp"'),
    );
  }

  protected function principle_3() {
    return array(
      new Step\When('I fill in "edit-principle-3-salmonella-spp-3-1" with "A critical limit"'),
      new Step\When('I fill in "edit-principle-3-salmonella-spp-3-2" with "The limit was determined by a technical method"'),
      new Step\When('I select "yes" from "principle_3[salmonella-spp][3_3]"'),
      new Step\When('I select "yes" from "principle_3[salmonella-spp][3_4]"'),
      new Step\When('I select "no" from "principle_3[salmonella-spp][3_5]"'),
      new Step\When('I fill in "edit-principle-3-stones-3-1" with "Another critical limit"'),
      new Step\When('I fill in "edit-principle-3-stones-3-2" with "The limit was determined by a simple method"'),
      new Step\When('I select "yes" from "principle_3[stones][3_3]"'),
      new Step\When('I select "yes" from "principle_3[stones][3_4]"'),
      new Step\When('I select "no" from "principle_3[stones][3_5]"'),
    );
  }

  protected function principle_4() {
    return array(
      new Step\When('I fill in "edit-principle-4-salmonella-spp-4-1" with "Some monitoring activities"'),
      new Step\When('I fill in "edit-principle-4-salmonella-spp-4-2" with "Once a week"'),
      new Step\When('I fill in "edit-principle-4-salmonella-spp-4-3" with "By a person"'),
      new Step\When('I fill in "edit-principle-4-salmonella-spp-4-4" with "Wilma Flintstone"'),
      new Step\When('I fill in "edit-principle-4-salmonella-spp-4-5" with "Fred Flintstone"'),
      new Step\When('I fill in "edit-principle-4-salmonella-spp-4-6" with "Log Book A"'),
      new Step\When('I select "no" from "principle_4[salmonella-spp][4_7]"'),
      new Step\When('I fill in "edit-principle-4-stones-4-1" with "Some monitoring activities"'),
      new Step\When('I fill in "edit-principle-4-stones-4-2" with "Twice a week"'),
      new Step\When('I fill in "edit-principle-4-stones-4-3" with "By the chief"'),
      new Step\When('I fill in "edit-principle-4-stones-4-4" with "Marcus Aurelius"'),
      new Step\When('I fill in "edit-principle-4-stones-4-6" with "Log Book B"'),
      new Step\When('I select "no" from "principle_4[stones][4_7]"'),
    );
  }

  protected function principle_5() {
    return array(
      new Step\When('I fill in "edit-principle-5-salmonella-spp-5-1" with "Discard the item"'),
      new Step\When('I fill in "edit-principle-5-salmonella-spp-5-2" with "Chef"'),
      new Step\When('I fill in "edit-principle-5-salmonella-spp-5-3" with "Bad product introduced"'),
      new Step\When('I fill in "edit-principle-5-salmonella-spp-5-4" with "On a monitoring sheet"'),
      new Step\When('I select "yes" from "principle_5[salmonella-spp][5_5]"'),
      new Step\When('I select "yes" from "principle_5[salmonella-spp][5_6]"'),
      new Step\When('I fill in "edit-principle-5-stones-5-1" with "Discard the item"'),
      new Step\When('I fill in "edit-principle-5-stones-5-2" with "Chef"'),
      new Step\When('I fill in "edit-principle-5-stones-5-3" with "Identification mistake"'),
      new Step\When('I fill in "edit-principle-5-stones-5-4" with "On a monitoring sheet"'),
      new Step\When('I select "yes" from "principle_5[stones][5_5]"'),
      new Step\When('I select "yes" from "principle_5[stones][5_6]"'),
    );
  }

  protected function principle_6() {
    return array(
      new Step\When('I fill in "edit-principle-6-6-1" with "Challenge testing the equipment"'),
      new Step\When('I fill in "edit-principle-6-6-2" with "Jane Doe"'),
      new Step\When('I select "yes" from "principle_6[6_3]"'),
      new Step\When('I check the box "principle_6[6_4][1][ccps]"'),
      new Step\When('I check the box "Records of monitoring"'),
      new Step\When('I check the box "Microbiological testing"'),
      new Step\When('I check the box "Third party certification(SOFHT, BRC)"'),
      new Step\When('I check the box "Deviations"'),
      new Step\When('I check the box "Product disposal"'),
      new Step\When('I fill in "edit-principle-6-6-5" with "No additional verification activity"'),
      new Step\When('I select the radio button "Yes" with the id "edit-principle-6-6-6-yes"'),
      new Step\When('I fill in "edit-principle-6-6-7" with "Annually"'),
      new Step\When('I fill in "edit-principle-6-6-8" with "Jane Doe"'),
      new Step\When('I check the box "Change of raw material supplier"'),
      new Step\When('I select the radio button "Yes" with the id "edit-principle-6-6-11-yes"'),
    );
  }

  /**
   * Returns an array of all stages in order.
   *
   * @return array
   *   The stages.
   */
  protected function getPrinciples() {
    return array(
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
    );
  }

}