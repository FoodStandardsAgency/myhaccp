@api
Feature: Preparatory G
  In order to complete Preparatory G
  As an authenticated user
  I need to be able to complete stage G

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "G" button

  Scenario: Complete Preparatory G and confirm data entry
    Given I select the radio button "Yes" with the id "edit-preparatory-g-g-1-yes"
    And I attach the file "file_good_1.jpg" to "edit-preparatory-g-g-2-upload"
    And I press the "Upload" button
    Then I should see "Remove"
    And I should not see "The file you uploaded does not appear to be a valid image file"

  Scenario: Test Preparatory G validation errors
    Given I select the radio button "No" with the id "edit-preparatory-g-g-1-no"
    When I press the "Save" button
    Then I should see "Please either upload a digital copy of your flow diagram"

  Scenario: Test Preparatory G bad file upload
    Given I select the radio button "No" with the id "edit-preparatory-g-g-1-no"
    And I attach the file "file_bad.jpg" to "edit-preparatory-g-g-2-upload"
    And I press the "Upload" button
    Then I should not see "Remove"
    And I should see "The file you uploaded does not appear to be a valid image file"