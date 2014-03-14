(function ($) {
  Drupal.behaviors.modalHelp = {
    attach: function(context) {
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
      $('footer a[href$="#close"]').click(function() {
        $('#dialog').dialog('close');
      });
    }
  }
})(jQuery);

var addToHomeConfig = {
  touchIcon: true,
  returningVisitor: true
};
