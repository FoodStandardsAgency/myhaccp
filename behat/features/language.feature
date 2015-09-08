@api
Feature: Language
  In order to log in to the web tool
  As an anonymous user
  I need to be able to log in to the site

  Scenario: Ensure the default language on registration option matches the site language
    Given I am on the homepage
    When I visit "/cy/user/register"
    # And I should see the link "Log in"
    Then the "Welsh (Cymraeg)" checkbox should be checked

    When I visit "user/register"
    Then the "English" checkbox should be checked