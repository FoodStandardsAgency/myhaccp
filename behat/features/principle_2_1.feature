@api
Feature: Principle 2 Question 1
  In order to complete Principle 2
  As an authenticated user
  I need to be able to complete stage 2.1

  Background:
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario:
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    Then I complete stage "1.3"
    And I press the "2.1" button
    When I select the radio button "Yes"
    And I select "Campden" from "1a"
    And I press the "2.2" button
    Then I should see "Q2a"
    And I should not see "Q1a"
