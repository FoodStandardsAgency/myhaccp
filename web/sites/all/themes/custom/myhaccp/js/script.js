(function ($) {
  Drupal.behaviors.modalHelp = {
    attach: function(context) {
      // Attach a click event to the dialog background so clicking it closes
      // the dialog.
      $('#dialog').on('dialogopen', function() {
        $('.ui-widget-overlay').bind('click', function() {
          $("#dialog").dialog('close');
        });
      });
      // Attach a click handler for the dialog's help menu links.
      $('.help-menu a').click(function(e) {
        // Get the attribute of the
        var link = $(this).attr('href');
        $('.help-menu ul li a').removeClass("active");
        $('.help-menu a[href$="' + link + '"]').addClass("active");
        $(link).removeClass("hidden").siblings("article").addClass("hidden");
        // Set the window's scroll position to 95 pixels down to avoid the
        // jump to top that is the default.
        $(window).scrollTop(-95);
        event.preventDefault();
      });
      // Add a click handler to close the dialog from the footer link.
      $('footer a[href$="#close"]').click(function() {
        $('#dialog').dialog('close');
      });
    }
  };

  Drupal.behaviors.customAnalytics = {
    attach: function(context) {

      $('a.complete-link, a.download-link').click(function() {
        // Determine the study url from the button href.
        var completeUrl = $(this).attr('href');
        var location = window.location.protocol +
          '//' + window.location.hostname +
          completeUrl;

        // Get the path elements.
        var pathArray = completeUrl.split('/');

        // Get the validity from the data attribute.
        var validity = parseInt($(this).attr('data-valid'));

        // Get the status of the study.
        var status = parseInt($(this).attr('data-status'));

        // Get the button label.
        var label = '';
        if (pathArray[4] == 'pdf') {
          label = 'PDF download';
        }
        else {
          if (pathArray[5].charAt(0) == '1') {
            label = 'Complete study';
          }
          else {
            label = 'Re-activate study';
          }
        }

        // Also send an event to GA.
        ga('send', {
          'hitType': 'event',
          'eventCategory': 'button',
          'eventAction': 'click',
          'eventLabel': label,
          'eventValue': validity + status
        });

        // Send a pageview for the complete button for better funnel tracking.
        if ($(this).attr('class') == 'complete-link') {
          ga('send', 'pageview', {
            'location': location,
            'page': completeUrl,
            'title': 'Complete study | MyHACCP'
          });
        }
      });

      // Trigger an event push to GA when the 'More information' link is
      // clicked. Pushes the help topic title as the label.
      $('a.use-dialog.more-link').click(function() {
        // Get the topic of the help from the data-topic attribute.
        var topic = $(this).attr('data-topic');
        ga('send', {
          'hitType': 'event',
          'eventCategory': 'help',
          'eventAction': 'open',
          'eventLabel': topic,
          'eventValue': 0
        });
      });

      $('#dialog .help-menu a').click(function(e) {
        var topic = $(this).text();
        ga('send', {
          'hitType': 'event',
          'eventCategory': 'help',
          'eventAction': 'change topic',
          'eventLabel': topic,
          'eventValue': 0
        });
      });

      // Send an event to GA when the help dialog is closed.
      $('#dialog').on('dialogclose', function() {
        ga('send', {
          'hitType': 'event',
          'eventCategory': 'help',
          'eventAction': 'close',
          'eventLabel': '',
          'eventValue': 0
        });
      });
    }
  };

})(jQuery);

var addToHomeConfig = {
  touchIcon: true,
  returningVisitor: true
};
