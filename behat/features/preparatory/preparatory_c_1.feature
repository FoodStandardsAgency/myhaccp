@api
Feature: Preparatory C.1
  In order to complete Preparatory C.1
  As an authenticated user
  I need to be able to complete stage C.1

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "C.1" button

  Scenario: Complete Preparatory C.1 and confirm data entry
    Given I select "Modular" from "1."
    And I fill in "2." with "Sauce"
    And I fill in "It will start at" with "Goods in"
    And I fill in "Through to" with "Dispatch"
    When I press the "Save and continue" button
    And I press the "Previous" button
    Then the "1." field should contain "Modular"
    And the "1." field should not contain "Linear"
    And the "2." field should contain "Sauce"
    And the "It will start at" field should contain "Goods in"
    And the "Through to" field should contain "Dispatch"

  Scenario: Test Preparatory C.1 validation errors
    Given I select "Modular" from "1."
    And I fill in "2." with ""
    And I fill in "It will start at" with ""
    And I fill in "Through to" with ""
    When I press the "Save this page" button
    Then I should see "The following items have errors you will need to correct"
    And I should see "2." in the ".parsley-error-list" element
    And I should see "It will start at" in the ".parsley-error-list" element
    And I should see "Through to" in the ".parsley-error-list" element


