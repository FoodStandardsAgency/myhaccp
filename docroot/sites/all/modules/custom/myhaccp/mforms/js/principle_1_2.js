/**
 * @file
 * Contains javascript helpers for principle 1 question 2.
 */

(function($) {

  Drupal.behaviors.principle_1_2 = {
    attach: function(context) {
      // Calculate significance from the values in severity and likelihood.
      $('input.severity, input.likelihood').bind('change, keyup', function(e) {
        var total = 0;
        // Fetch the row.
        var $row = $(this).parent().parent().parent();
        // Get the severity field value.
        var severity = $row.find('input.severity').val();
        // Check if severity is greater than three or less than one and if so
        // reset the field to empty.
        if (severity > 3 || severity < 1) {
          $row.find('input.severity').val('');
          severity = 0;
        }
        // Get the likelihood field value.
        var likelihood = $row.find('input.likelihood').val();
        // Check if likelihood is greater than three or less than one and if so
        // reset the field to empty.
        // @todo: Put in some kind of message.
        if (likelihood > 3 || likelihood < 1) {
          $row.find('input.likelihood').val('');
          likelihood = 0;
        }
        // Calculate the total.
        total = parseFloat(severity * likelihood);
        // If the total isn't zero then update the significance field value.
        if (total != 0) {
          var sig = $row.find('input.significance');
          sig.val(total);
        }
      });
    }
  }
})(jQuery);
