@api
Feature: Preparatory H
  In order to complete Preparatory H
  As an authenticated user
  I need to be able to complete stage H

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "H" button

  Scenario: Complete Preparatory H and confirm data entry
    Given I fill in "1." with "John Doe"
    And I select the radio button "Yes" with the id "edit-preparatory-h-h-2-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-h-h-3-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-h-h-4-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-h-h-5-yes"
    And I select the radio button "Yes" with the id "edit-preparatory-h-h-6-yes"
    And I fill in "7." with "Jane Doe"


    When I press the "Save this page" button

    Then the "1." field should contain "John Doe"
    And the radio button with id "edit-preparatory-h-h-2-yes" should be checked
    And the radio button with id "edit-preparatory-h-h-3-yes" should be checked
    And the radio button with id "edit-preparatory-h-h-4-yes" should be checked
    And the radio button with id "edit-preparatory-h-h-5-yes" should be checked
    And the radio button with id "edit-preparatory-h-h-6-yes" should be checked
    And the "7." field should contain "Jane Doe"


  Scenario: Test Preparatory H validation errors
    Given I fill in "1." with "John Doe"
    And I select the radio button "No" with the id "edit-preparatory-h-h-2-no"
    And I select the radio button "No" with the id "edit-preparatory-h-h-3-no"
    And I select the radio button "No" with the id "edit-preparatory-h-h-4-no"
    And I select the radio button "No" with the id "edit-preparatory-h-h-5-no"
    And I select the radio button "No" with the id "edit-preparatory-h-h-6-no"
    And I fill in "7." with "Jane Doe"

    When I press the "Save this page" button

    Then I should see "The following items have errors you will need to correct"
    And I should see "2." in the ".parsley-error-list" element
    And I should see "3." in the ".parsley-error-list" element
    And I should see "4." in the ".parsley-error-list" element
    And I should see "5." in the ".parsley-error-list" element
    And I should see "6." in the ".parsley-error-list" element