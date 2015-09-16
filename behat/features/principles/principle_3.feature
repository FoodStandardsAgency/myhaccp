@api
Feature: Principle 3
  In order to complete Principle 3
  As an authenticated user
  I need to be able to complete stage 3

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 3
    Given I complete all principles up to "2.2"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-3-salmonella-spp-3-1 | A critical limit |
      | edit-principle-3-salmonella-spp-3-2 | The limit was determined by a technical method |
    And I select "yes" from "principle_3[salmonella-spp][3_3]"
    And I select "yes" from "principle_3[salmonella-spp][3_4]"
    And I select "no" from "principle_3[salmonella-spp][3_5]"
    When I fill in the following:
      | edit-principle-3-stones-3-1 | Another critical limit |
      | edit-principle-3-stones-3-2 | The limit was determined by a simple method |
    And I select "yes" from "principle_3[stones][3_3]"
    And I select "yes" from "principle_3[stones][3_4]"
    And I select "no" from "principle_3[stones][3_5]"
    And I press the "Save this page" button
    Then I should not see an ".parsley-error-list" element

  Scenario: Test validation for Principle 3
    Given I complete all principles up to "2.2"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-3-salmonella-spp-3-2 | The limit was determined by a technical method |
    And I select "yes" from "principle_3[salmonella-spp][3_3]"
    And I select "yes" from "principle_3[salmonella-spp][3_4]"
    And I select "no" from "principle_3[salmonella-spp][3_5]"
    When I fill in the following:
      | edit-principle-3-stones-3-1 | Another critical limit |
      | edit-principle-3-stones-3-2 | The limit was determined by a simple method |
    And I select "yes" from "principle_3[stones][3_3]"
    And I select "yes" from "principle_3[stones][3_4]"
    And I select "no" from "principle_3[stones][3_5]"
    And I press the "Save this page" button
    Then I should see "Study saved"
    And I should see "1. What is the critical limit for this critical control point" in the ".parsley-error-list" element

