@api
Feature: Principle 6
  In order to complete Principle 6
  As an authenticated user
  I need to be able to complete stage 6

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 6
    Given I complete all principles up to "5"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-6-6-1 | Challenge testing the equipment |
      | edit-principle-6-6-2 | Jane Doe |
    And I select the radio button "Yes" with the id "edit-principle-6-6-3-yes"
    And I check the box "principle_6[6_4][1][ccps]"
    And I check the box "Records of monitoring"
    And I check the box "Microbiological testing"
    And I check the box "Third party certification(SOFHT, BRC)"
    And I check the box "Deviations"
    And I check the box "Product disposal"
    And I fill in "edit-principle-6-6-5" with "No additional verification activity"
    And I select the radio button "Yes" with the id "edit-principle-6-6-6-yes"
    And I fill in "edit-principle-6-6-7" with "Annually"
    And I fill in "edit-principle-6-6-8" with "Jane Doe"
    And I check the box "Change of raw material supplier"
    And I select the radio button "Yes" with the id "edit-principle-6-6-11-yes"
    And I press the "Save this page" button
    And I should not see an ".parsley-error-list" element
    And the "Critical Control Points" checkbox should be checked

  Scenario: Test validation for Principle 6
    Given I complete all principles up to "5"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-6-6-1 | Challenge testing the equipment |
      | edit-principle-6-6-2 | Jane Doe |
    And I press the "Save this page" button
    Then I should see "Study saved"
    And should see 6 ".parsley-error-list li" elements
    And I should see "8. Who is responsible for carrying out a formal annual review?" in the ".parsley-error-list" element

