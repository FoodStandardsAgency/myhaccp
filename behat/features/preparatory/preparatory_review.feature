@api
Feature: Preparatory Review
  In order to complete the Preparatory stages
  As an authenticated user
  I need to be able to review all stages

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "preparatory_review" button

  Scenario: Confirm the review introductory text exists
    Then I should see "This section provides an overview of progress made in completing the Preparatory Stages of your HACCP study"

  Scenario: Confirm the review main text exists
    Then I should see "If all the Preparatory Stages are marked as OK then you are ready to move to the Principle stages"
