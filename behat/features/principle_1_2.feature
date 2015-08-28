@api
Feature: Principle 1 Question 2
  In order to complete Principle 1
  As an authenticated user
  I need to be able to complete stage 1.1 and 1.2

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "1.1" button

  Scenario: Check that previous stages have been filled in
    Given I complete all principles up to "1.1"
    And I press the "Save and continue" button
    Then I should see "Stones"
    And I should see "Salmonella spp."
    And I should see "Sesame seeds"

  Scenario:
    Given I complete all principles up to "1.1"
    And I press the "Save and continue" button
    When I fill row "1" "description" with "A description"
    And I fill row "1" "severity" with "3"
    And I fill row "1" "likelihood" with "3"
    And I fill row "1" "significance" with "9"
    Then I fill row "2" "description" with "Stones description"
    And I fill row "2" "severity" with "3"
    And I fill row "2" "likelihood" with "2"
    And I fill row "2" "significance" with "6"
    Then I fill row "3" "description" with "Another description"
    And I fill row "3" "severity" with "1"
    And I fill row "3" "likelihood" with "2"
    And I fill row "3" "significance" with "2"
    Then I fill in "Determine the threshold" with "5"
    And I press the "Save and continue" button
    Then I should see "(1) A step in my process"
    And I should not see "Sesame seeds"
    And I should see "Stones"
    And I should see "Stones description"

# Scenario:
#     Given I complete all principles up to "1.1"
#     And I press the "Save and continue" button
#     When I fill row "1" "description" with "A description"
#     And I fill row "1" "severity" with "3"
#     And I fill row "1" "likelihood" with "3"
#     And I fill row "1" "significance" with "9"
#     Then I fill row "2" "description" with "Stones description"
#     And I fill row "2" "severity" with "3"
#     And I fill row "2" "likelihood" with "2"
#     And I fill row "2" "significance" with "6"
#     Then I fill row "3" "description" with "Another description"
#     And I fill row "3" "severity" with "1"
#     And I fill row "3" "likelihood" with "2"
#     And I fill row "3" "significance" with "2"
#     Then I fill in "Determine the threshold" with "5"
#     And I press the "Save this page" button
#     Then I should see "A description"

