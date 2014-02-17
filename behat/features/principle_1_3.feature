@api
Feature: Principle 1 Question 3
  In order to complete Principle 1
  As an authenticated user
  I need to be able to complete stages 1.1, 1.2 and 1.3

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 1.3 with two control measures
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    And I fill row "1" "control-measure" with "My control measure"
    And I fill row "2" "control-measure" with "Another control measure"
    And I press the "2.2" button
    Then I should see "Another control measure"
    And I should see "Control measure"

  Scenario: Test validation for Principle 1.3
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    And I fill row "1" "control-measure" with "My control measure"
    And I press the "Save and continue" button
    And I press the "Previous" button
    Then I should see "Please add a control measure."
