@api
Feature: Principle 2 Question 2
  In order to complete Principle 2
  As an authenticated user
  I need to be able to complete stage 2.2

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 2.2 with one CCP
    Given I complete all principles up to "2.1"
    And I press the "Save and continue" button
    When I select the radio button "Yes" in row "1" "ccp"
    When I select the radio button "No" in row "2" "ccp"
    And I press the "Save and continue" button
    Then I should see "Control Measure: My control measure"
    And I should not see "Control Measure: Another control measure"

  Scenario: Complete Principle 2.2 with two CCPs
    Given I complete all principles up to "2.1"
    And I press the "Save and continue" button
    When I select the radio button "Yes" in row "1" "ccp"
    When I select the radio button "Yes" in row "2" "ccp"
    And I press the "Save and continue" button
    Then I should see "Control Measure: My control measure"
    And I should see "Control Measure: Another control measure"

  Scenario: Test validation for Principle 2.2
    Given I complete all principles up to "2.1"
    And I press the "Save and continue" button
    When I select the radio button "Yes" in row "1" "ccp"
    And I press the "Save this page" button
    Then I should see "Study saved"
    And I should see "Please indicate whether this process step is a critical control point"

