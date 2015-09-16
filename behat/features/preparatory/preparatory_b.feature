@api
Feature: Preparatory B
  In order to complete Preparatory B
  As an authenticated user
  I need to be able to complete stage B

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "B" button

  Scenario: Complete Preparatory B and confirm data entry
    Given I check "N/A - I am the management and can confirm that I am committed."
    And I check "A Food Safety Policy has been drawn up and signed by management."
    And I check "Senior management document, support and communicate their food safety policies."
    And I check "Minutes of HACCP team meetings."
    And I check "Senior management support the work of the HACCP team."
    And I check "Resources identified by the HACCP team are made available as required to develop, implement and maintain the HACCP system."
    And I check "Training takes place for HACCP studies."
    And I fill in "2." with "lorem ipsum"

    When I press the "Save this page" button

    Then the "N/A - I am the management and can confirm that I am committed." checkbox should be checked
    And the "A Food Safety Policy has been drawn up and signed by management." checkbox should be checked
    And the "Senior management document, support and communicate their food safety policies." checkbox should be checked
    And the "Minutes of HACCP team meetings." checkbox should be checked
    And the "Senior management support the work of the HACCP team." checkbox should be checked
    And the "Resources identified by the HACCP team are made available as required to develop, implement and maintain the HACCP system." checkbox should be checked
    And the "Training takes place for HACCP studies." checkbox should be checked
    And the "2." field should contain "lorem ipsum"

  Scenario: Test Preparatory B validation errors
    Given I fill in "2." with ""

    When I press the "Save this page" button

     Then I should see "The following items have errors you will need to correct"
     And I should see "2." in the ".parsley-error-list" element