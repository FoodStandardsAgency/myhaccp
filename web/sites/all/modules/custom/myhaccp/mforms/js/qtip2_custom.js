(function($) {

  Drupal.behaviors.qtip2_custom = {
    attach: function(context) {
      // Prepare the tooltips by iterating over each help-tip element and
      // checking for some help text.
      $('.help-tip').once().each(function() {
        // Check if there is a help-text element to render.
        var help_text = $(this).parents('.form-item, th, div.label').children('.help-text');
        // Get the question to push to GA as an event label.
        var question = $(this).parent().clone().children().remove().end().text();
        // Determine the stage.
        // Get the path elements.
        var location = window.location.pathname;
        var pathArray = location.split('/');

        var phase = pathArray[4];
        var stage = pathArray[5];
        question = phase + '/' + stage + ' - ' + question;

        // If we have some help text then move on and add the tooltip.
        if (help_text.length > 0) {
          // Disable the usual click event on the button.
          $(this).click(false);
          // Enable the qtip on the button.
          $(this).qtip({
            content: {
              text: help_text
            },
            position: {
              my: 'top center',
              at: 'bottom center',
              target: $(this),
              viewport: $('.main-wrapper'),
              adjust: {
                method: 'shift'
              }
            },
            style: {
              classes: 'qtip-haccp',
              tip: {
                corner: true,
                width: 12
              }
            },
            show: {
              event: 'hover',
              delay: 180,
              effect: function(offset) {
                $(this).fadeIn(400);
              }
            },
            hide: {
              delay: 500,
              fixed: true,
              effect: function(offset) {
                $(this).fadeOut(400);
              }
            },
            events: {
              show: function(event, api) {
                // Send an event to Google Analytics.
                // Fetch the current question.
                ga('send', {
                  'hitType': 'event',
                  'eventCategory': 'help',
                  'eventAction': 'inline',
                  'eventLabel': question
                });
              }
            }
          });
        }
      });

      $('.more-link').click(function() {
        $('div.qtip:visible').qtip('hide');
      });

    }
  }

})(jQuery);
