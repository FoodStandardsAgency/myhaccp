@api
Feature: Principle 4
  In order to complete Principle 4
  As an authenticated user
  I need to be able to complete stage 4

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 4
    Given I complete all principles up to "3"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-4-salmonella-spp-4-1 | Some monitoring activities |
      | edit-principle-4-salmonella-spp-4-2 | Once a week |
      | edit-principle-4-salmonella-spp-4-3 | By a person |
      | edit-principle-4-salmonella-spp-4-4 | Wilma Flintstone |
      | edit-principle-4-salmonella-spp-4-5 | Fred Flintstone |
      | edit-principle-4-salmonella-spp-4-6 | Log Book A |
    And I select "no" from "principle_4[salmonella-spp][4_7]"
    When I fill in the following:
      | edit-principle-4-stones-4-1 | Some monitoring activities |
      | edit-principle-4-stones-4-2 | Twice a week |
      | edit-principle-4-stones-4-3 | By the chief |
      | edit-principle-4-stones-4-4 | Marcus Aurelius |
      | edit-principle-4-stones-4-6 | Log Book B |
    And I select "no" from "principle_4[stones][4_7]"
    And I press the "Save this page" button
    Then I should not see an ".parsley-error-list" element

  Scenario: Test validation for Principle 4
    Given I complete all principles up to "3"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-4-salmonella-spp-4-1 | Some monitoring activities |
      | edit-principle-4-salmonella-spp-4-2 | Once a week |
      | edit-principle-4-salmonella-spp-4-3 | By a person |
      | edit-principle-4-salmonella-spp-4-4 | Wilma Flintstone |
      | edit-principle-4-salmonella-spp-4-5 | Fred Flintstone |
      | edit-principle-4-salmonella-spp-4-6 | Log Book A |
    And I select "no" from "principle_4[salmonella-spp][4_7]"
    And I press the "Save this page" button
    Then I should see "Study saved"
    And should see 7 ".parsley-error-list li" elements
    And I should see "1. What monitoring activities are going to take place at this CCP?" in the ".parsley-error-list" element
    And I should see "4. Who is responsible for monitoring actions at this CCP?" in the ".parsley-error-list" element

