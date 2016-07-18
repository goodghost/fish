<div class="work-delegation-dashboard">
  <div class="dashboard-column">
    <h4><?php print $my_own_dashboard ? t("My team's cases") : t("User's team cases"); ?>:</h4>
    <div id="team-cases" class="dashboard-column-droppable">
      <?php foreach ($my_team_cases as $team_case): ?>
        <div class="dashboard-card" data-case="<?php print $team_case['Case Encoded']; ?>" id="<?php print $team_case['id'];?>">
          <div class="category"><span><?php print $team_case['Priority']; ?></span></div>
          <div class="left">
            <div class="item"><?php print t('Case Ref'); ?>: <strong><?php print $team_case['Case Reference']; ?></strong></div>
            <div class="item"><?php print t('Team'); ?>: <strong><?php print $team_case['Team']; ?></strong></div>
            <div class="item"><?php print t('Owner'); ?>: <strong><?php print $team_case['Owner']; ?></strong></div>
          </div>
          <div class="right">
            <div class="item"><?php print t('Age'); ?>: <strong><?php print $team_case['Case Age']; ?></strong></div>
            <div class="item"><?php print t('Status'); ?>: <strong><?php print $team_case['Case Status']; ?></strong></div>
          </div>
        </div>
      <?php endforeach; ?>
    </div>
  </div>

  <div class="dashboard-column">
    <h4><?php print $my_own_dashboard ? t('My cases') : t("User's cases"); ?>:</h4>
    <div id="my-cases" class="dashboard-column-droppable">
      <?php foreach ($my_cases as $my_case): ?>
        <div class="dashboard-card" data-case="<?php print $my_case['Case Encoded']; ?>" id="<?php print $my_case['id'];?>">
          <div class="category"><span><?php print $my_case['Priority']; ?></span></div>
          <div class="left">
            <div class="item"><?php print t('Case Ref'); ?>: <strong><?php print $my_case['Case Reference']; ?></strong></div>
            <div class="item"><?php print t('Team'); ?>: <strong><?php print $my_case['Team']; ?></strong></div>
            <div class="item"><?php print t('Owner'); ?>: <strong><?php print $my_case['Owner']; ?></strong></div>
          </div>
          <div class="right">
            <div class="item"><?php print t('Age'); ?>: <strong><?php print $my_case['Case Age']; ?></strong></div>
            <div class="item"><?php print t('Status'); ?>: <strong><?php print $my_case['Case Status']; ?></strong></div>
          </div>
        </div>
      <?php endforeach; ?>
    </div>
  </div>
</div>

<div class="card-info">
  <h4><?php print t('Case details'); ?>:</h4>
  <div class="card-info-content">
    <div class="item first">
      <div class="case-details case-details-reference"><?php print t('Case Reference'); ?>: <strong><span></span></strong></div>
      <div class="case-details case-details-type"><?php print t('Case Type'); ?>: <strong><span></span></strong></div>
      <div class="case-details case-details-date-created"><?php print t('Date Case Created'); ?>: <strong><span></span></strong></div>
      <div class="case-details case-details-owner"><?php print t('Case Owner'); ?>: <strong><span></span></strong></div>
    </div>
    <div class="item">
      <div class="case-details case-details-team"><?php print t('Assigned to Team'); ?>: <strong><span></span></strong></div>
      <div class="case-details case-details-priority"><?php print t('Assigned Priority'); ?>: <strong><span></span></strong></div>
    </div>
    <div class="item last">
      <div class="case-details case-details-target-date"><?php print t('Target Date'); ?>: <strong><span></span></strong></div>
      <div class="case-details case-details-retailer"><?php print t('Retailer'); ?>: <strong><span></span></strong></div>
    </div>
  </div>
</div>
