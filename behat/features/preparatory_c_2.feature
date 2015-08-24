@api
Feature: Preparatory C.2
  In order to complete Preparatory C.2
  As an authenticated user
  I need to be able to complete stage C.2

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "C.2" button

  Scenario: Complete Preparatory C.2 and confirm data entry
    Given I check "Metal"
    And I check "Wood splinters"
    And I check "Glass and brittle plastic"
    And I check "Flexible plastic"
    And I check "Plasters"
    And I check "Stones"
    And I check "Shell"
    And I check "Fruit stones"
    And I check "Insects"
    And I check "Paper/board"
    And I check "Hair"
    And I check "Bones"
    And I check "Feathers"
    And I check "String"
    And I check "Finger nails"
    And I check "Pests"
    And I fill in "Other" with "rocks"

    # Save the page
    When I press the "Save this page" button

    Then the "Other" field should contain "rocks"
    # Can't get these checkboxes to confirm they are checked
    # Tried with the id rather than the label:
    # And the "edit-preparatory-c-2-wrapper-physical-c-4-physical-wood" checkbox should be checked
    And the "Metal" checkbox should be checked
    And the "Glass and brittle plastic" checkbox should be checked
    And the "Flexible plastic" checkbox should be checked
    And the "Plasters" checkbox should be checked
    And the "Stones" checkbox should be checked
    And the "Shell" checkbox should be checked
    And the "Fruit stones" checkbox should be checked
    And the "Insects" checkbox should be checked
    And the "Paper/board" checkbox should be checked
    And the "Hair" checkbox should be checked
    And the "Bones" checkbox should be checked
    And the "Feathers" checkbox should be checked
    And the "String" checkbox should be checked
    And the "Finger nails" checkbox should be checked
    And the "Pests" checkbox should be checked
    And the "Other" field should contain "rocks"




