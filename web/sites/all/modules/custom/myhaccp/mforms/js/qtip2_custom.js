(function($) {

  Drupal.behaviors.qtip2_custom = {
    attach: function(context) {
      // Prepare the tooltips by iterating over each help-tip element and
      // checking for some help text.
      $('.help-tip').each(function() {
        // Check if there is a help-text element to render.
        var help_text = $(this).parent().parent().children('.help-text');
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
              target: $(this)
            },
            style: {
              classes: 'qtip-haccp'
            },
            show: {
              event: 'click'
            },
            hide: {
              event: 'unfocus, click'
            }
          });
        }
      });
    }
  }

})(jQuery);
