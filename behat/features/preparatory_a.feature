@api
Feature: Preparatory A
  In order to complete Preparatory A
  As an authenticated user
  I need to be able to complete stage A

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "A" button

  Scenario: Complete Preparatory A and confirm data entry
    Given I check "Supplier approval"
    And I check "Glass and plastic management"
#    When I press the "Save and continue" button
#    And I press the "Previous" button
    Then the "Supplier approval" checkbox should be checked
    And the "Glass and plastic management" checkbox should be checked
    And the "Pest Control" checkbox should not be checked

  Scenario: Test Preparatory A validation errors
    Given I check the box "Glass and plastic management"
    When I press the "Save and continue" button
    And I press the "Previous" button
    Then I should see "Please specify the location of the above documents."
