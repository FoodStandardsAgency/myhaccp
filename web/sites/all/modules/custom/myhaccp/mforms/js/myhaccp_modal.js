/**
 * Provide the HTML to create the modal dialog.
 */
(function($) {
  Drupal.theme.prototype.myhaccp_modal = function() {
    console.log('loaded');
    alert('loaded');
    $('nav .help-menu ul li a').click(function() {
      var link = $(this).attr('href');
      $('nav .help-menu ul li a[href$="' + link + '"]').parent().addClass("active").siblings("li").removeClass("active");
      $("#" + link).removeClass("hidden").siblings("article").addClass("hidden");
      $(".ui-dialog").scrollTop(0)
    });


//    "#/" + this.settings.guidancePath + "/" + a !== window.location.hash && (window.location.hash = "#/" + this.settings.guidancePath + "/" + a),

  }
})(jQuery);
