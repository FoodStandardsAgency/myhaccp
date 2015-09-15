@api
Feature: Language on registration forms
  In order to store my default language
  As an anonymous user
  On the registration form I expect the language to be my current language

  Scenario: As a Welsh person I want the default language selected to be Welsh
    Given I am on the homepage
    When I visit "/cy/user/register"
    Then the "Cymraeg" checkbox should be checked
    Then the "English" checkbox should not be checked

  Scenario: As a English person I want the default language selected to be English
    Given I am on the homepage
    When I visit "user/register"
    Then the "English" checkbox should be checked
    Then the "Cymraeg" checkbox should not be checked