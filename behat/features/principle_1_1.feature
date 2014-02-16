@api
Feature: Principle 1 Question 1
  In order to complete Principle 1
  As an authenticated user
  I need to be able to complete stage 1.1

  Background:
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario:
    Given I fill in "Step no." with "1"
    And I fill in "Step name" with "A step in my process"
    And I fill in "Biological" with "Salmonella spp."
    And I fill in "Allergens" with "Sesame seeds"
    And I fill in "Physical" with "Stones"
    When I press the "Save and continue" button
    Then I should see "Salmonella spp." in the "tr:nth-of-type(1) td" element
    And I should see "Stones" in the "tr:nth-of-type(2) td" element
    And I should see "Sesame seeds" in the "tr:nth-of-type(3) td" element
