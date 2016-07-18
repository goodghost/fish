<?php

/**
 * @file
 * Migrations for fr_user.
 */

class UsersMigration extends FrMigration {

  public function __construct($arguments = array()) {
    parent::__construct($arguments);

    $this->description = t('Import users from CSV file.');
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'fr_user') . '/import/users.csv', array(), array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();

    // Create a map object for tracking the relationships between source rows.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'name' => array(
          'type' => 'varchar',
          'length' => 64,
          'not null' => TRUE,
          'description' => 'The user name.',
        ),
      ),
      $this->destination->getKeySchema()
    );

    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('mail', 'mail');
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('role_names', 'role_names');

    // Default values.
    $this->addFieldMapping('status')->defaultValue(1);
  }
}
