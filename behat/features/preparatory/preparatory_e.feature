@api
Feature: Preparatory E
  In order to complete Preparatory E
  As an authenticated user
  I need to be able to complete stage E

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "E" button

  Scenario: Complete Preparatory E and confirm data entry
    Given I fill in "1." with "Lorem Ipsum"
    And I fill in "2." with "Lorem Ipsum"
    And I fill in "3." with "Lorem Ipsum"
    And I fill in "4." with "Lorem Ipsum"
    And I fill in "5." with "Lorem Ipsum"
    And I fill in "6." with "Lorem Ipsum"
    And I fill in "7." with "Lorem Ipsum"

    When I press the "Save this page" button

    Then the "1." field should contain "Lorem Ipsum"
    And the "2." field should contain "Lorem Ipsum"
    And the "3." field should contain "Lorem Ipsum"
    And the "4." field should contain "Lorem Ipsum"
    And the "5." field should contain "Lorem Ipsum"
    And the "6." field should contain "Lorem Ipsum"
    And the "7." field should contain "Lorem Ipsum"

  Scenario: Test Preparatory E validation errors
    Given I fill in "1." with "Lorem Ipsum"
    And I fill in "2." with ""
    And I fill in "3." with ""
    And I fill in "4." with ""
    And I fill in "5." with ""
    And I fill in "6." with ""
    And I fill in "7." with ""

    When I press the "Save this page" button

    Then I should see "The following items have errors you will need to correct"
    And I should see "2." in the ".parsley-error-list" element
    And I should see "3." in the ".parsley-error-list" element
    And I should see "4." in the ".parsley-error-list" element
    And I should see "5." in the ".parsley-error-list" element
    And I should see "6." in the ".parsley-error-list" element
    And I should see "7." in the ".parsley-error-list" element