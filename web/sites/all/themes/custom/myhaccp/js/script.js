(function ($) {
  Drupal.behaviors.modalHelp = {
    attach: function(context) {
      $('.help-menu a').click(function(e) {
        var link = $(this).attr('href');
<<<<<<< Updated upstream
        $('.help-menu ul li a').removeClass("active");
        $('.help-menu a[href$="' + link + '"]').addClass("active");
=======
        $('.help-menu a[href$="' + link + '"]').parents('nav').find('li').removeClass("active");
        $('.help-menu a[href$="' + link + '"]').parent().addClass("active");
>>>>>>> Stashed changes
        $(link).removeClass("hidden").siblings("article").addClass("hidden");
        $(".ui-widget-overlay").scrollTop(0);
      });
    }
  }
})(jQuery);

var addToHomeConfig = {
  touchIcon: true,
  returningVisitor: true
};
