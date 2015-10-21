@api
Feature: Language switcher in header
  In order to switch languages
  As an anonymous user
  On any page I should be able to choose Welsh language

  Scenario: As a Welsh person I want to see a language switcher
    Given I am on the homepage
    Then I should see "Languages"
    And I should see "Cymraeg"

  Scenario: As a Welsh person I want to change the language to Welsh
    Given I am on the homepage
    And I follow "Cymraeg"
    Then I should not see "MyHACCP is aimed at small food manufacturing businesses in the UK"
    And I should see "Mae MyHACCP wedi’i hanelu at fusnesau gweithgynhyrchu bwyd bach yn y Deyrnas Unedig"
