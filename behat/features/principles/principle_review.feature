@api
Feature: Principle Review
  In order to complete the Principles
  As an authenticated user
  I need to be able to review all stages

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "principle_review" button

  Scenario: Confirm the review introductory text exists
    Then I should see "This section provides an overview of progress made in completing the Principles stages of your HACCP Study"

  Scenario: Confirm the review main text exists
    Then I should see "If all principle stages are completed they will be flagged as 'OK' above"
