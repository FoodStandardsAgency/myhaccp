<?php

use Drupal\DrupalExtension\Context\DrupalContext,
    Drupal\DrupalExtension\Event\EntityEvent;

use Behat\Behat\Exception\PendingException,
    Behat\Behat\Context\Step;

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
   * @When /^I complete stage "([^"]*)"$/
   */
  public function iCompleteStage($stage) {
    $function = 'stage_' . str_replace('.', '_', $stage);
    return $this->$function();
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
    echo $target;
    $field = $this->getSession()->getPage()->find('css', $target);
    // Check if we found a field.
    if (NULL === $field) {
      throw new ElementNotFoundException($this->getSession(), 'form field', 'css', $field);
    }
    // Set the field's value.
    $field->setValue($value);
  }

  protected function stage_1_1() {
    return array(
      new Step\When('I fill in "Step no." with "1"'),
      new Step\Then('I fill in "Step name" with "A step in my process"'),
      new Step\Then('I fill in "Biological" with "Salmonella spp."'),
      new Step\Then('I fill in "Allergens" with "Sesame seeds"'),
      new Step\Then('I fill in "Physical" with "Stones"')
    );
  }

  protected function stage_1_2() {
    return array(
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][salmonella-spp][description]" with "A description"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][salmonella-spp][severity]" with "3"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][salmonella-spp][likelihood]" with "3"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][salmonella-spp][significance]" with "9"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][stones][description]" with "Another description"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][stones][severity]" with "3"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][stones][likelihood]" with "2"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][stones][significance]" with "6"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][sesame-seeds][description]" with "Stones description"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][sesame-seeds][severity]" with "1"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][sesame-seeds][likelihood]" with "2"'),
      new Step\Then('I fill in "principle_1_2[a-step-in-my-process][instance_table][sesame-seeds][significance]" with "2"'),
      new Step\Then('I fill in "principle_1_2[threshold]" with "6"'),
    );
  }

}
