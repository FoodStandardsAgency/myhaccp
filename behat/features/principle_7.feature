@api
Feature: Principle 7
  In order to complete Principle 7
  As an authenticated user
  I need to be able to complete stage 7

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 7
    Given I complete all principles up to "6"
    And I press the "Save and continue" button
    When I check the box "Product description"
    And I check the box "The monitoring plan for each CCP"
    And I fill in "edit-principle-7-7-2" with "No additional supporting documentation"
    And I fill in "edit-principle-7-7-3" with "Computer based"
    And I fill in "edit-principle-7-7-4" with "1 year"
    And I select the radio button "Yes" with the id "edit-principle-7-7-5-yes"
    And I press the "Save this page" button
    And I should not see an ".parsley-error-list" element
    And the "Product description" checkbox should be checked

  Scenario: Test validation for Principle 7
    Given I complete all principles up to "6"
    And I press the "Save and continue" button
    And I fill in "edit-principle-7-7-2" with "No additional supporting documentation"
    And I press the "Save this page" button
    Then I should see "Study saved"
    And should see 5 ".parsley-error-list li" elements
    And I should see "4. What is the maximum length of time that you retain this information for" in the ".parsley-error-list" element

