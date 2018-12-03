(function ($) {

  Drupal.behaviors.siteMapContent = {
    attach: function (context, settings) {
      $('#edit-site-map-content input.form-checkbox', context).once('site-map-content', function () {
        var $checkbox = $(this);
        // Retrieve the tabledrag row belonging to this content.
        var $row = $('#' + $checkbox.attr('id').replace(/-show-/, '-order-'), context).closest('tr');

        // Bind click handler to this checkbox to conditionally show and hide the
        // filter's tableDrag row.
        $checkbox.bind('click.siteMapUpdate', function () {
          if ($checkbox.is(':checked')) {
            $row.show();
          }
          else {
            $row.hide();
          }
          // Restripe table after toggling visibility of table row.
          Drupal.tableDrag['site-map-order'].restripeTable();
        });

        // Trigger our bound click handler to update elements to initial state.
        $checkbox.triggerHandler('click.siteMapUpdate');
      });
    }
  };

})(jQuery);
