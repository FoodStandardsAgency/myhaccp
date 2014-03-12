(function ($) {
  Drupal.behaviors.modalHelp = {
    attach: function(context) {
      $('.help-menu a').click(function(e) {
        var link = $(this).attr('href');
        $('.help-menu ul li a').removeClass("active");
        $('.help-menu a[href$="' + link + '"]').addClass("active");
        $(link).removeClass("hidden").siblings("article").addClass("hidden");
        $(".ui-widget-overlay").scrollTop(0)
      });
    }
  }
})(jQuery);

var addToHomeConfig = {
  touchIcon: true,
  returningVisitor: true
};
