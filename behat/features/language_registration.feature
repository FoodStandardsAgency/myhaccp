@api
Feature: Language on registration forms
  In order to store my default language
  As an anonymous user
  On the registration form I expect the language to be my current language

  Scenario: As a Welsh person I want the default language selected to be Welsh
    Given I am on the homepage
    When I visit "/cy/user/register"
    Then the "Cymraeg" radio button should be selected
    And I should see "Saesneg (English)"
    And the "Saesneg (English)" radio button should not be selected

  Scenario: As a English person I want the default language selected to be English
    Given I am on the homepage
    When I visit "user/register"
    Then the "English" radio button should be selected
    And I should see "Welsh (Cymraeg)"
    And the "Welsh (Cymraeg)" radio button should not be selected