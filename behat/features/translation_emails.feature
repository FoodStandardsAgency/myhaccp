@api
Feature: Translate emails
  In order to translate emails
  As a translator
  I need to be able to translate emails

  Background: 
    Given I am logged in as a user with the "administrator" role
    And I visit "/admin/config/people/accounts"
    Then I should see "The are multiligual variables in this form"

    Scenario:
        Given I am logged in as a user with the "administrator" role
    	And I visit "/admin/config/people/accounts"
    	Then I should see "There are multilingual variables in this form"

    Scenario: Administrator can translate
    	Given I am logged in as a user with the "administrator" role 
    	And I visit "/admin/config/people/accounts"
    	When I follow "Welsh"
    	And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email"
    	And I press the "Save configuration" button
    	Then I should see "The configuration options have been saved."

    Scenario: Check the admin can translate the Welsh and it doesnt overwrite the English
    	Given I am logged in as a user with the "administrator" role
    	And I visit "/admin/config/people/accounts"
    	When I follow "Welsh"
    	And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email content for the welcome - new user"
    	And I press the "Save configuration" button
    	Then I should see "The configuration options have been saved."
        Then the "edit-user-mail-register-admin-created-body" field should contain "Welsh email content for the welcome - new user"

    	When I follow "English" 
    	Then the "edit-user-mail-register-admin-created-body" field should not contain "Welsh email content for the welcome - new user"

    Scenario: Check the admin can edit the English and it doesnt overwrite the Welsh translations
        Given I am logged in as a user with the "administrator" role
        And I visit "/admin/config/people/accounts"
        When I follow "English"
        And I fill in "edit-user-mail-register-admin-created-body" with "English email content for the welcome - new user"
        And I press the "Save configuration" button
        Then I should see "The configuration options have been saved."
        Then the "edit-user-mail-register-admin-created-body" field should contain "English email content for the welcome - new user"

        When I follow "Welsh" 
        Then the "edit-user-mail-register-admin-created-body" field should not contain "English email content for the welcome - new user"

    Scenario: Check the admin can edit the English and doesnt overwrite the Welsh default text
    	Given I am logged in as a user with the "administrator" role
    	And I visit "/admin/config/people/accounts"
    	When I follow "English"
    	And I fill in "edit-user-mail-status-blocked-body" with "English email for blocked email"
    	And I press the "Save configuration" button
    	Then I should see "The configuration options have been saved."
        Then the "edit-user-mail-status-blocked-body" field should contain "English email for blocked email"

    	When I follow "Welsh" 
    	Then the "edit-user-mail-status-blocked-body" field should not contain "English email for blocked email"

    Scenario: Check the translator can edit the Welsh, and it saves
        Given I am logged in as a user with the "translator" role
        And I visit "/admin/config/people/accounts"
        When I follow "Welsh"
        And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email by a translator"
        When I press the "Save configuration" button
        Then I should see "The configuration options have been saved."
        Then the "edit-user-mail-register-admin-created-body" field not contain "Welsh email by a translator"

    Scenario: Check the translator can edit the Welsh, and doesnt overwrite the English
    	Given I am logged in as a user with the "translator" role
    	And I visit "/admin/config/people/accounts"
    	When I follow "Welsh"
    	And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email by a translator"
    	And I press the "Save configuration" button
    	And I should see "The configuration options have been saved."
        And the "edit-user-mail-register-admin-created-body" field not contain "Welsh email by a translator" 

    	When I follow "English" 
    	Then the "edit-user-mail-register-admin-created-body" field should not contain "Welsh email by a translator"

    Scenario: Check the translator can edit the English, and it doesnt overwrite the Welsh translation
    	Given I am logged in as a user with the "translator" role
    	And I visit "/admin/config/people/accounts"
    	And I follow "English"
    	And I fill in "edit-user-mail-register-admin-created-body" with "English email text"
    	And I press the "Save configuration" button
    	And I should see "The configuration options have been saved."
        And the "edit-user-mail-register-admin-created-body" field should contain "English email text"

        When I follow "Welsh"
        Then the "edit-user-mail-register-admin-created-body" field should not contain "English email text"

   Scenario: Check the translator can edit the English and doesnt overwrite the Welsh default text
        Given I am logged in as a user with the "translator" role
        And I visit "/admin/config/people/accounts"
        When I follow "English"
        And I fill in "edit-user-mail-status-blocked-body" with "English email for blocked email from translator"
        And I press the "Save configuration" button
        And I should see "The configuration options have been saved."
        And the "edit-user-mail-status-blocked-body" field should contain "English email for blocked email from translator"

        When I follow "Welsh" 
        Then the "edit-user-mail-status-blocked-body" field should not contain "English email for blocked email from translator"

