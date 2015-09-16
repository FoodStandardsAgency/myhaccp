@api
Feature: Preparatory F
  In order to complete Preparatory F
  As an authenticated user
  I need to be able to complete stage F

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "F" button

  Scenario: Complete Preparatory F and confirm data entry
    Given I fill in "1." with "Lorem Ipsum"
    And I select the radio button "No" with the id "edit-preparatory-f-f-2-no"
    And I select the radio button "Yes" with the id "edit-preparatory-f-f-3-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-f-f-4-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-f-f-5-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-f-f-6-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-f-f-7-yes"
    And I fill in "8." with "Lorem Ipsum"


    When I press the "Save this page" button

    Then the "1." field should contain "Lorem Ipsum"
    And the radio button with id "edit-preparatory-f-f-2-no" should be checked
    And the radio button with id "edit-preparatory-f-f-3-yes" should be checked
    And the radio button with id "edit-preparatory-f-f-4-yes" should be checked
    And the radio button with id "edit-preparatory-f-f-5-yes" should be checked
    And the radio button with id "edit-preparatory-f-f-6-yes" should be checked
    And the radio button with id "edit-preparatory-f-f-7-yes" should be checked
    And the "8." field should contain "Lorem Ipsum"


  Scenario: Test Preparatory F validation errors
    Given I fill in "1." with "Lorem Ipsum"
    And I fill in "8." with ""

    When I press the "Save this page" button

    Then I should see "The following items have errors you will need to correct"
    And I should see "8." in the ".parsley-error-list" element