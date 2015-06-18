@api
Feature: Principle 5
  In order to complete Principle 5
  As an authenticated user
  I need to be able to complete stage 5

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Complete Principle 5
    Given I complete all principles up to "4"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-5-salmonella-spp-5-1 | Discard the item |
      | edit-principle-5-salmonella-spp-5-2 | Chef |
      | edit-principle-5-salmonella-spp-5-3 | Bad product introduced |
      | edit-principle-5-salmonella-spp-5-4 | On a monitoring sheet |
    And I select "yes" from "principle_5[salmonella-spp][5_5]"
    And I select "yes" from "principle_5[salmonella-spp][5_6]"
    When I fill in the following:
      | edit-principle-5-stones-5-1 | Discard the item |
      | edit-principle-5-stones-5-2 | Chef |
      | edit-principle-5-stones-5-3 | Identification mistake |
      | edit-principle-5-stones-5-4 | On a monitoring sheet |
    And I select "yes" from "principle_5[stones][5_5]"
    And I select "yes" from "principle_5[stones][5_6]"
    And I press the "Save this page" button
    Then I should not see an ".parsley-error-list" element

  Scenario: Test validation for Principle 4
    Given I complete all principles up to "4"
    And I press the "Save and continue" button
    When I fill in the following:
      | edit-principle-5-salmonella-spp-5-1 | Discard the item |
      | edit-principle-5-salmonella-spp-5-2 | Chef |
      | edit-principle-5-salmonella-spp-5-3 | Bad product introduced |
      | edit-principle-5-salmonella-spp-5-4 | On a monitoring sheet |
    And I select "yes" from "principle_5[salmonella-spp][5_5]"
    And I select "yes" from "principle_5[salmonella-spp][5_6]"
    And I press the "Save this page" button
    Then I should see "Study saved"
    And should see 7 ".parsley-error-list li" elements
    And I should see "1. Corrective action to be taken." in the ".parsley-error-list" element

