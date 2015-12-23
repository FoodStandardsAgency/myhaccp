(function($) {

  Drupal.behaviors.closeblock = {

    attach: function (context, settings) {

      if (settings.closeblock == undefined) {
        return;
      }

      $.each(settings.closeblock, function(id, info) {
        $('#'+ id  + ':not(.closeblock-processed)', context).addClass('closeblock-processed').each(function() {
          var
            $block = $(this);

          if (info.closed) {
            $block.hide();
            return;
          }

          var
            $close_button = $('<span />').addClass('closeblock-button').html(Drupal.t('close')),
            $close_container = $('<div />').addClass('closeblock').append($close_button);

          $block.prepend($close_container);

          $close_button.click(function() {
            if (info.type) {
              $block[info.type](info.speed);
            }
            else {
              $block.hide();
            }
            if (info.save) {
              $.ajax({
                type: 'POST',
                url: Drupal.settings.basePath + ['closeblock', info.module, info.delta].join('/')
              });
            }
          });
        });
      });

    }

  };

})(jQuery);
