@api
Feature: Principle 2 Question 1
  In order to complete Principle 2
  As an authenticated user
  I need to be able to complete stage 2.1

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 2.1 selecting Campden decision tree
    Given I complete all principles up to "1.3"
    And I press the "Save and continue" button
    When I select the radio button "Yes"
    And I select "Campden" from "1a"
    And I press the "2.2" button
    Then I should see "Q2a"
    And I should not see "Q1a"

  Scenario: Complete Principle 2.1 selecting Codex decision tree
    Given I complete all principles up to "1.3"
    And I press the "Save and continue" button
    When I select the radio button "Yes"
    And I select "Codex" from "1a"
    And I press the "2.2" button
    Then I should see "Q1a"
    And I should not see "Q2a"

  Scenario: Complete Principle 2.1 selecting no decision tree
    Given I complete all principles up to "1.3"
    And I press the "Save and continue" button
    When I select the radio button "No"
    And I press the "2.2" button
    Then I should not see "Q1a"
    And I should not see "Q2a"
