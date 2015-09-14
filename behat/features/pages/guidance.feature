@api
Feature: Guidance
  In order to view the guidance
  As an anonymous user
  I need to be able to navigate to and view the guidance section

  Scenario: View the downloads section
    Given I visit "/help/guidance/resources"
    And I should see "This section contains a range of useful reference material on HACCP in general"

  Scenario: Click through to the external links section
    Given I am on "/help/guidance/resources"
    And I follow "External links"
    And I should see "This section contains links to information on external websites"
