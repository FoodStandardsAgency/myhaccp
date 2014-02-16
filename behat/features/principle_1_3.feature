@api
Feature: Principle 1 Question 3
  In order to complete Principle 1
  As an authenticated user
  I need to be able to complete stages 1.1, 1.2 and 1.3

  Background:
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario:
    Given I complete stage "1.1"
    And I press the "Save and continue" button
    Then I complete stage "1.2"
    And I press the "Save and continue" button
    And I fill in "principle_1_3[instance_table][salmonella-spp][control_measure]" with "My control measure"
    And I fill in "principle_1_3[instance_table][stones][control_measure]" with "Another control measure"
    And I press the "2.2" button
    Then I should not see "Another control measure"
