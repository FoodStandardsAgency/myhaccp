(function ($) {
  Drupal.behaviors.modalHelp = {
    attach: function(context) {
      $('.help-menu a').click(function(e) {
        var link = $(this).attr('href');
        $('.help-menu a[href$="' + link + '"]').parents('nav').find('li').removeClass("active");
        $('.help-menu a[href$="' + link + '"]').parent().addClass("active");
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
