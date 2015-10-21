@api
Feature: Preparatory D
  In order to complete Preparatory D
  As an authenticated user
  I need to be able to complete stage D

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "D" button

  Scenario: Complete Preparatory D and confirm data entry
    Given I fill in "Name of HACCP lead for the business" with "John Doe"
    And I fill in "Relevant training" with "Lorem Ipsum dolor"
    And I fill in "Qualifications" with "Lorem Ipsum dolor amet"
    And I fill in "Relevant experience" with "Lorem Ipsum"
    And I select the radio button "Yes"

    When I press the "Save this page" button

    Then the "Name of HACCP lead for the business" field should contain "John Doe"
    And the "Relevant training" field should contain "Lorem Ipsum dolor"
    And the "Qualifications" field should contain "Lorem Ipsum dolor amet"
    And the "Relevant experience" field should contain "Lorem Ipsum"
    And the "Yes" checkbox should be checked

  Scenario: Test Preparatory D validation errors
    Given I fill in "Name of HACCP lead for the business" with "John Doe"
    And I fill in "Relevant training" with "Lorem Ipsum dolor"
    And I fill in "Qualifications" with "Lorem Ipsum dolor amet"
    And I fill in "Relevant experience" with ""
    And I select the radio button "Yes"

    When I press the "Save this page" button

    Then I should see "The following items have errors you will need to correct"
    And I should see "Relevant experience" in the ".parsley-error-list" element