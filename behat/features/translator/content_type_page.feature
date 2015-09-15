@api
Feature: Translate Page Content Type
  In order to translate page content
  As a translator user
  I need to be able to enter a translation and confirm its existence

  Background: Log in as a translator user
    Given I am logged in as a user with the "translator" role

  Scenario: Ensure basic page content type is translatable
    Given I visit "/node/92/edit"
    And I select "English" from "Language"
    And I press "Save"
    Then I should see "Translate"

  Scenario: Create a basic page node and translate it
    Given I am viewing a "page" node with the title "MyHACCP test page"
    And I follow "Edit"
    And I select "English" from "Language"
    And for "Body" I enter "Body field"
    And I press "Save"
    And I follow "Translate"
    And I follow "add"
    And for "Title" I enter "[Welsh] MyHACCP test page"
    And for "Body" I enter "[Welsh] Body field"
    And I press "Save"
    Then I should see "[Welsh] MyHACCP test page"
    And I should see "[Welsh] Body field"