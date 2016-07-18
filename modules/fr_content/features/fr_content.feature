Feature: Creating dashboards
  In order to see dashboards with reports
  I should be able to create groups, reports and dashboards

  @javascript
  Scenario: Creating group, report and dashboard
    ############################################################################
    # Log in as builder
    ############################################################################

    Given I am on "/user"
    And I fill in "name" with "builder"
    And I fill in "pass" with "builder"
    And I press "edit-submit"

    ############################################################################
    # Create group
    ############################################################################

    # Navigate to group add form
    And I go to "/node/add/group"
    # Fill title
    And I fill in "title" with "Group 1"
    # Save content
    And I press "Save"
    # Test if it's added properly
    And I should see "Group 1"

    ############################################################################
    # Create report
    ############################################################################

    # Navigate to report add form
    And I go to "/node/add/report"
    # Fill title
    And I fill in "title" with "Report 1"
    # Fill dataset field
    And I select "Album Print Queue" from "Dataset view"
    And I wait 2 seconds
    # Display few fields
    And I check "field_dataset[und][0][fields][field:id][enabled]"
    And I check "field_dataset[und][0][fields][field:UserName][enabled]"
    And I check "field_dataset[und][0][fields][field:UserID][enabled]"
    # Add filter number 1
    And I press "Add filter"
    And I wait 2 seconds
    And I fill in "field_dataset[und][0][filters][table][field_0]" with "id"
    And I fill in "field_dataset[und][0][filters][table][operator_0]" with ">="
    And I fill in "field_dataset[und][0][filters][table][value_0]" with "10"
    And I check "field_dataset[und][0][filters][table][exposed_0]"
    # Add filter number 2
    And I press "Add filter"
    And I fill in "field_dataset[und][0][filters][table][field_1]" with "UserID"
    And I fill in "field_dataset[und][0][filters][table][operator_1]" with ">="
    And I fill in "field_dataset[und][0][filters][table][value_1]" with "500"
    # Remove filter number 2
    And I click on the element with css selector "#edit-field-dataset-und-0-filters-table-remove-1--2"
    # Select group
    And I select "Group 1" from "og_group_ref[und][0][default][]"
    # Save content
    And I press "Save"
    # Test if it's added properly
    And I should see "Report 1"

    ############################################################################
    # Create dashboard
    ############################################################################

    # Navigate to dashboard add form
    And I go to "/node/add/dashboard"
    # Fill title
    And I fill in "title" with "Dashboard 1"
    # Select group
    And I select "Group 1" from "og_group_ref[und][0][default][]"
    # Save content
    And I press "Save"
    # Test if it's added properly
    And I should see "Dashboard 1"
