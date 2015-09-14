@api
Feature: Translate Page Content Type
  In order to translate resource content
  As a translator user
  I need to be able to enter a translation and confirm its existence

  Background: Log in as a translator user
    Given I am logged in as a user with the "translator" role

  Scenario: Ensure an existing resource (download) node is translatable
    Given I visit "/node/60/edit"
    And I select "English" from "Language"
    And I press "Save"
    Then I should see "Translate"

  Scenario: Ensure an existing resource (link) node is translatable
    Given I visit "/node/97/edit"
    And I select "English" from "Language"
    And I press "Save"
    Then I should see "Translate"
