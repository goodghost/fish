<?php

use Behat\Behat\Context\ClosuredContextInterface,
  Behat\Behat\Context\TranslatedContextInterface,
  Behat\Behat\Context\BehatContext,
  Behat\Behat\Exception\PendingException,
  Behat\Gherkin\Node\PyStringNode,
  Behat\Gherkin\Node\TableNode,
  Behat\MinkExtension\Context\MinkContext,
  Behat\Behat\Context\Step\Given,
  Behat\Behat\Context\Step\When,
  Behat\Behat\Context\Step\Then;


// Require 3rd-party libraries here:
//
// require_once 'PHPUnit/Autoload.php';
// require_once 'PHPUnit/Framework/Assert/Functions.php';

/**
 * Features context.
 */
class FeatureContext extends MinkContext
{
  /**
   * Initializes context.
   * Every scenario gets it's own context object.
   *
   * @param array $parameters context parameters (set them up through behat.yml)
   */
  public function __construct(array $parameters) {
    // Initialize your context here
  }

  /**
   * @Given /^I wait for page to load$/
   */
  public function iWaitForPageToLoad() {
    $this->getSession()->wait(4000);
  }

  /**
   * Click on the element with the provided CSS Selector
   *
   * @When /^I click on the element with css selector "([^"]*)"$/
   */
  public function iClickOnTheElementWithCSSSelector($cssSelector) {
    $session = $this->getSession(); // get the mink session
    $element = $session->getPage()->find('css', $cssSelector);

    if (!$element) {
      throw new \InvalidArgumentException(sprintf('Could not evaluate CSS Selector: "%s"', $cssSelector));
    }

    $element->click();
  }

  /**
   * Click on one of the Drupal primary tab based on tab number
   *
   * @Given /^I click on the primary tab number (\d+)$/
   */
  public function iClickOnThePrimaryTabNumber($tabNumber) {
    $session = $this->getSession(); // get the mink session

    if (!$element = $session->getPage()->find('css', "ul.tabs.primary li:nth-child($tabNumber) a")) {
      if (!$element = $session->getPage()->find('css', "ul.tabs--primary li:nth-child($tabNumber) a")) {
        throw new \InvalidArgumentException(sprintf('Could not find %d tab inside primary tabs', $tabNumber));
      }
    }

    $element->click();
  }

  /**
   * Click on one of the Drupal primary tab
   *
   * @Given /^I click on the primary tab "([^"]*)"$/
   */
  public function iClickOnThePrimaryTab($tabText) {
    $session = $this->getSession(); // get the mink session

    if (!$tabs = $session->getPage()->findAll('css', "ul.tabs.primary a")) {
      if (!$tabs = $session->getPage()->findAll('css', "ul.tabs--primary  a")) {
        throw new \InvalidArgumentException(sprintf('Could not find primary tabs'));
      }
    }

    foreach ($tabs as $tab) {
      if ($tab->getText() == $tabText) {
        $tab->click();
        return;
      }
    }

    throw new \InvalidArgumentException(sprintf('Could not find %s tab inside primary tabs', $tabText));
  }

  /**
   * Wait specific numbers of seconds.
   *
   * @Given /^I wait (\d+) (\w+)?$/
   */
  public function iWait($time, $unit) {
    switch ($unit) {
      case 'second':
      case 'seconds':
        $time = $time * 1000;
        break;
      case 'minute':
      case 'minutes':
      $time = $time * 60000;
        break;
    }
    $this->getSession()->wait($time);
  }

}
