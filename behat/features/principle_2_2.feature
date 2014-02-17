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
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    Then I complete stage "1.3"
    And I press the "2.1" button
    When I select the radio button "Yes"
    And I select "Campden" from "1a"
    And I press the "2.2" button
    When I select the radio button "Yes" in row "1" "ccp"
    When I select the radio button "No" in row "2" "ccp"
    And I press the "Save and continue" button
    Then I should see "Control Measure: My control measure"
    And I should not see "Control Measure: Another control measure"

  Scenario: Complete Principle 2.2 with two CCPs
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    Then I complete stage "1.3"
    And I press the "2.1" button
    When I select the radio button "Yes"
    And I select "Campden" from "1a"
    And I press the "2.2" button
    When I select the radio button "Yes" in row "1" "ccp"
    When I select the radio button "Yes" in row "2" "ccp"
    And I press the "Save and continue" button
    Then I should see "Control Measure: My control measure"
    And I should see "Control Measure: Another control measure"

  Scenario: Test validation for Principle 2.2
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    Then I complete stage "1.3"
    And I press the "2.1" button
    When I select the radio button "No"
    And I press the "Save and continue" button
    And I press the "Save this page" button
    Then I should see "Please indicate whether this process step is a critical control point."
