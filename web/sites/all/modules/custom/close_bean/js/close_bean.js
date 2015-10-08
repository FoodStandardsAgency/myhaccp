(function($) {

  Drupal.behaviors.close_bean = {

    attach: function (context, settings) {

      if (settings.close_bean == undefined) {
        return;
      }

      console.log(settings.close_bean);

      $.each(settings.close_bean, function(delta, info) {
        $('.' + delta  + ':not(.close-bean-processed)', context).addClass('close-bean-processed').each(function() {
          var $block = $(this);

          console.log(info);
          if (info.closed) {
            $block.hide();
            return;
          }

          var $close_button = $('<span />').addClass('close-bean-button').html(Drupal.t('Close')),
            $close_container = $('<div />').addClass('close-bean').append($close_button);

          $block.prepend($close_container);

          $close_button.click(function() {
            if (info.type) {
              $block[info.type](info.speed);
            }
            else {
              $block.hide();
            }
            $.ajax({
              type: 'POST',
              url: Drupal.settings.basePath + ['closebean', info.delta].join('/')
            });
          });
        });
      });

    }

  };

})(jQuery);
