@api
Feature: Registration
  In order register in to the web tool
  As an anonymous user
  I need to be able to register on to the site

  Scenario: Ensure the register link is visible on the home page
    Given I am on the homepage
    Then I should see the heading "MyHACCP"
    And I should see the link "Register"

  Scenario: Ensure the registration fields are storing data
    Given I am on the homepage
    And I am an anonymous user
    And I visit "/user/register"
    
    And I fill in "Username" with "uniquename"
    And I fill in "E-mail address" with "unique@email.com"
    And I select "United Kingdom" from "Country"
    And I select "5 - 10" from "Size of business"
    And I fill in "Postcode area" with "OX"
    And I select "Prepared meals" from "Business type"
    And I check "I agree to the MyHACCP terms and conditions."
    When I press the "edit-submit" button
    
    Then I should not see "The name uniquename is already taken."
    And I should not see "The e-mail address unique@email.com is already registered. Have you forgotten your password?"
    And I should not see "Business type field is required."
    And I should not see "Postcode area field is required."
    And I should not see "I agree to the MyHACCP terms and conditions. field is required."
    And I should not see "Size of business field is required"
    And I should not see "Country field is required"
    And I should not see "Please fill out this field."
    And I should not see "Fields marked with an asterisk (*) are required."
    And I should see "Further instructions have been sent to your e-mail address."

    
    # And I am logged in as a user with the "administrator" role
    # And I visit "/admin/people"
    # And I fill in "E-mail" with "unique@email.com"
    # And I press the "Apply" button

    # Then I should not see "No users available."


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
      And I should not see "Password must have at least 9 character(s)." in the ".error ul" element

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
      Then I should not see "Your current password is missing or incorrect; it's required to change the Password."
      And I should see "Password must have at least 1 symbol(s)." in the ".error ul" element
      And I should not see "Password must have upper and lower case letters." in the ".error ul" element
      And I should not see "Password must have at least 9 character(s)." in the ".error ul" element

Scenario: Password authentication
Given users:
      | name   | mail         | pass    |
      | _bob   | _bob@foo.com | uniqueP4ss! |
      And I am logged in as "_bob"
      And I visit "/user"
      And I follow "Edit"
      And I fill in "Current password" with "uniqueP4ss!"
      And I fill in "Password" with "!Abcdef"
      And I fill in "Confirm password" with "!Abcdef"
      
      When I press the "Save" button
      Then I should not see "Your current password is missing or incorrect; it's required to change the Password."
      Then I should not see "Password must have at least 1 symbol(s)." in the ".error ul" element
      And I should not see "Password must have upper and lower case letters." in the ".error ul" element
      And I should see "Password must have at least 9 character(s)." in the ".error ul" element

Scenario: Password authentication
Given users:
      | name   | mail         | pass    |
      | _bob   | _bob@foo.com | uniqueP4ss! |
      And I am logged in as "_bob"
      And I visit "/user"
      And I follow "Edit"
      And I fill in "Current password" with "uniqueP4ss!"
      And I fill in "Password" with "!Abcdefgh"
      And I fill in "Confirm password" with "!Abcdefgh"
      
      When I press the "Save" button
      Then I should not see "Your current password is missing or incorrect; it's required to change the Password."
      And I should not see "Password must have at least 1 symbol(s)." in the ".error ul" element
      And I should not see "Password must have upper and lower case letters." in the ".error ul" element
      And I should not see "Password must have at least 9 character(s)." in the ".error ul" element
      And I should see "The changes have been saved."

  Scenario: Password authentication
Given users:
      | name   | mail         | pass    |
      | _bob   | _bob@foo.com | uniqueP4ss! |
      And I am logged in as "_bob"
      And I visit "/user"
      And I follow "Edit"
      And I fill in "Current password" with "uniqueP4ss!"
      And I select the radio button "Welsh (Cymraeg)"

      When I press the "Save" button
      Then I should see "The changes have been saved."
