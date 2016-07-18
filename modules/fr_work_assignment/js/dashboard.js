/**
 * @file
 * Dashboard for case management.
 */

(function($) {

  Drupal.behaviors.fr_work_assignment_dashboard = {
    attach: function(context, settings) {
      var $teamCases = $('#team-cases'),
          $myCases = $('#my-cases'),
          $cardInfo = $('.card-info'),
          $card = $('.dashboard-card');

      // Prevent cases to resize when dragging.
      $card.width($card.width());

      function moveCard(card, column) {
        card.css({position: '', left: '', top: '', visibility: 'hidden'}).hide(function() {
          card.appendTo(column).css({visibility: 'visible'}).slideDown();
        });
      }

      // Helper function for setting equal heights of containers.
      function equalHeight(group) {
        var $element = $(group);
        var tallest = 0;
        $element.each(function() {
          var thisHeight = jQuery(this).height();
          if (thisHeight > tallest) {
            tallest = thisHeight;
          }
        });
        $element.css({'min-height': tallest});
      }

      // Send data ny AJAX.
      function sendData(event, ui, target) {
        // Prevent of reloading window when AJAX request is still in progress.
        function preventClosingWindow() {
          return Drupal.t("Saving your changes is still in progress. If you leve this page your changes won't be saved.");
        }
        $(window).bind('beforeunload', preventClosingWindow);

        $.ajax({
          url: Drupal.settings.fr_work_assignment.updatePath,
          type: 'POST',
          data: {
            'form_token': Drupal.settings.fr_work_assignment.formToken,
            'case_id': ui.draggable.attr('id'),
            'target': target
          },
          dataType: 'json',
          complete: function (options) {
            $(window).unbind('beforeunload', preventClosingWindow);
          }
        });
      }

      // Open info about selected case.
      function openCardInfo($element) {
        var $cardInfoContent = $cardInfo.find('.card-info-content');
        var caseData = $element.data('case');

        $cardInfoContent.find('.case-details-reference span').text(caseData['Case Reference']);
        $cardInfoContent.find('.case-details-type span').text('?');
        $cardInfoContent.find('.case-details-date-created span').text(caseData['Case Date']);
        $cardInfoContent.find('.case-details-team span').text(caseData['Team']);
        $cardInfoContent.find('.case-details-priority span').text(caseData['Priority']);
        $cardInfoContent.find('.case-details-target-date span').text(caseData['Target Date']);
        $cardInfoContent.find('.case-details-retailer span').text(caseData['Retailer']);
        $cardInfoContent.find('.case-details-owner span').text(caseData['Owner']);

        $cardInfo.slideDown('fast');
      }

      // Enable dragging of cases.
      $('.dashboard-column-droppable .dashboard-card').draggable({
        revert: 'invalid',
        containment: 'document',
        start: function(event, ui) {
          equalHeight('.dashboard-column-droppable');
        }
      });

      // Enable selecting of cases.
      $card.bind('mousedown', function(event) {
        var $selectedCard = $(this);

        if (!$selectedCard.hasClass('selected')) {
          $('.dashboard-card').removeClass('selected');
          $selectedCard.addClass('selected');

          openCardInfo($selectedCard);
        }
      });

      // Enable dropping to "My cases" container.
      $myCases.droppable({
        accept: '#team-cases .dashboard-card',
        activeClass: 'ui-state-highlight',
        hoverClass: 'ui-state-active',
        tolerance: 'pointer',
        drop: function(event, ui) {
          moveCard(ui.draggable, $myCases);
          sendData(event, ui, 'user');
        }
      });

      // Enable dropping to "My team's cases" container.
      $teamCases.droppable({
        accept: '#my-cases .dashboard-card',
        activeClass: 'ui-state-highlight',
        hoverClass: 'ui-state-active',
        tolerance: 'pointer',
        drop: function(event, ui) {
          moveCard(ui.draggable, $teamCases);
          sendData(event, ui, 'team');
        }
      });

    }
  };

})(jQuery);


