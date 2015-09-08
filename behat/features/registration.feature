@api
Feature: Registration
  In order register in to the web tool
  As an anonymous user
  I need to be able to register on to the site

  Scenario: Ensure the register link is visible on the home page
    Given I am on the homepage
    Then I should see the heading "MyHACCP"
    And I should see the link "Register"

  Scenario: Ensure the registeration fields are storing data
    Given I am on the homepage
    And I am an anonymous user
    And I visit "/user/register"
    
    And I fill in "Username" with "unique name"
    And I fill in "E-mail address" with "unique@email.com"
    And I select "United Kingdom" from "Country"
    And I select "5 - 10" from "Size of business"
    And I fill in "Postcode" with "OX"
    And I select "Prepared meals" from "Business type"
    And I check "I agree to the MyHACCP terms and conditions."
    When I press the "Create new account" button
    And I am logged in as a user with the "authenticated user" role
    And I visit "/user"
     # Then I should see "Main profile"

   # Scenario: Send an email when a user registers
  #   Given I am on "user/register"
  #   And I fill in "Username" with "unique name"
  #   And I fill in "E-mail address" with "unique@email.com"
  #   And I select "United Kingdom" from "Country"
  #   And I select "5 - 10" from "Size of business"
  #   And I fill in "Postcode" with "OX"
  #   And I select "Prepared meals" from "Business type"
  #   And I check "I agree to the MyHACCP terms and conditions."
  #   Then an email should be sent to "unique@email.com"

  Scenario: Password authentication
    Given users:
      | name   | mail         | pass    |
      | _bob   | _bob@foo.com | uniqueP4ss! |
      And I am logged in as "_bob"
      And I visit "/user"
      And I follow "Edit"
      And I fill in "Current password" with "uniqueP4ss!"
      And I fill in "Password" with "abcdefghij"
      And I fill in "Confirm password" with "abcdefghij"
      
      When I press the "Save" button
      # Then I should see "Your current password is missing or incorrect; it's required to change the Password."
      Then I should see "Password must have upper and lower case letters." in the ".error ul" element
      And I should see "Password must have at least 1 symbol(s)." in the ".error ul" element

Scenario: Password authentication
Given users:
      | name   | mail         | pass    |
      | _bob   | _bob@foo.com | uniqueP4ss! |
      And I am logged in as "_bob"
      And I visit "/user"
      And I follow "Edit"
      And I fill in "Current password" with "uniqueP4ss!"
      And I fill in "Password" with "Abcdefghij"
      And I fill in "Confirm password" with "Abcdefghij"
      
      When I press the "Save" button
      # Then I should see "Your current password is missing or incorrect; it's required to change the Password."
      Then I should see "Password must have at least 1 symbol(s)." in the ".error ul" element
      And I should not see "Password must have upper and lower case letters." in the ".error ul" element
