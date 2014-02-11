(function($) {

  Drupal.behaviors.qtip2_custom = {
    attach: function(context) {
      // Prepare the tooltips by iterating over each help-tip element and
      // checking for some help text.
      $('.help-tip').once().each(function() {
        // Check if there is a help-text element to render.
        var help_text = $(this).parents('.form-item, th, div.label').children('.help-text');
        // If we have some help text then move on and add the tooltip.
        if (help_text.length > 0) {
          // Disable the usual click event on the button.
          $(this).click(false);

//          // Fetch the anchor destination from the element. There may not be any
//          // guidance in which case don't add the more info link.
//          var href = $(this).attr('href');
//          if (href !== '#') {
//            var help_link = ' <a class="more-information" target="_blank" href="' + href + '">More information</a>';
//            help_text.append(help_link);
//          }
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
