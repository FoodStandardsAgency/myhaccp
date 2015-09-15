@api
Feature: Homepage
  In order to view the homepage
  As an anonymous user
  I need to be able to navigate to the homepage and ensure it is visible

  Scenario: View the homepage
    Given I visit "/"
    Then I should see "Helping you produce safe food"
    And I should see "Who is this site for?"
    And I should see "What next?"

  Scenario: Navigate back to the home page from another page
    Given I am on "/help/guidance/resources"
    And I follow "Home"
    Then I should be on the homepage
