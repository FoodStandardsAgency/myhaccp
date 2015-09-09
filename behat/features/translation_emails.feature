@api
Feature: Translate emails
  In order to translate emails
  As a translator
  I need to be able to translate emails

  # Background: 
  #   Given I am logged in as a user with the "administrator" role
  #   And I visit "/admin/config/people/accounts"
  #   Then I should see "The are multiligual variables in this form"

    Scenario:
        Given I am logged in as a user with the "administrator" role
    	And I visit "/admin/config/people/accounts"
    	Then I should see "There are multilingual variables in this form"

    Scenario: 
    	Given I am logged in as a user with the "administrator" role 
    	And I visit "/admin/config/people/accounts"
    	When I follow "Welsh"
    	And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email"
    	And I press the "Save configuration" button
    	Then I should see "The configuration options have been saved."

    Scenario: 
    	Given I am logged in as a user with the "administrator" role
    	And I visit "/admin/config/people/accounts"
    	When I follow "Welsh"
    	And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email"
    	And I press the "Save configuration" button
    	Then I should see "The configuration options have been saved."

    	When I follow "English" 
    	Then the "edit-user-mail-register-admin-created-body" field should not contain "Welsh email"

    # Scenario: 
    # 	Given I am logged in as a user with the "administrator" role
    # 	And I visit "/admin/config/people/accounts"
    # 	When I follow "English"
    # 	And I fill in "edit-user-mail-status-blocked-body" with "English email"
    # 	And I press the "Save configuration" button
    # 	Then I should see "The configuration options have been saved."

    # 	When I follow "Welsh" 
    # 	Then the "edit-user-mail-status-blocked-body" field should not contain "English email"

    Scenario: 
    	Given I am logged in as a user with the "translator" role
    	And I visit "/admin/config/people/accounts"
    	When I follow "Welsh"
    	And I fill in "edit-user-mail-register-admin-created-body" with "Welsh email by a translator"
    	And I press the "Save configuration" button
    	Then I should see "The configuration options have been saved."

    	When I follow "English" 
    	Then the "edit-user-mail-register-admin-created-body" field should not contain "Welsh email by a translator"

    # Scenario: 
    # 	Given I am logged in as a user with the "translator" role
    # 	And I visit "/admin/config/people/accounts"
    # 	When I follow "English"
    # 	And I fill in "edit-user-mail-status-blocked-body" with "English email by a translator"
    # 	And I press the "Save configuration" button
    # 	Then I should see "The configuration options have been saved."

    # 	When I follow "Welsh" 
    # 	Then the "edit-user-mail-status-blocked-body" field should not contain "English email by a translator"