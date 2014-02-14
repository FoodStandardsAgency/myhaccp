Feature: Log in
  In order to log in to the web tool
  As an anonymous user
  I need to be able to log in to the site
  
  Scenario: Ensure the login link is visible on the home page
    Given I am on the homepage
    Then I should see the heading "MyHACCP"
    And I should see the link "Log in"
