# features/search.feature
Feature: User
  In order to use the site as an auth user,
  I should be able to log in and log out

  Scenario: Logging admin in and out
    Given I am on "/user"
    When I fill in "name" with "admin"
    And I fill in "pass" with "admin"
    And I press "edit-submit"
    Then I should see "admin"
    And I should see "Member for"
    And I follow "Log out"
    Then I should see "Welcome to eeShore"
