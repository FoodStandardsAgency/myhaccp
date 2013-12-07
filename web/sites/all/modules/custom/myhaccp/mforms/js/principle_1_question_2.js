/**
 * @file
 * Contains javascript helpers for principle 1 question 2.
 */

(function($) {

  Drupal.behaviors.p1q2 = {
    attach: function(context) {
      // Calculate significance from the values in severity and likelihood.
      $('.form-item.severity input, .form-item.likelihood input').change(function(e) {
        var total = 0;
        // Fetch the row.
        var $row = $(this).parent().parent().parent();
        // Get the severity field value.
        var severity = $row.find('.form-item.severity input').val();
        // Check if severity is greater than three or less than one and if so
        // reset the field to empty.
        // @todo: Put in some kind of message.
        if (severity > 3 || severity < 1) {
          $row.find('.form-item.severity input').val('');
          severity = 0;
        }
        // Get the likelihood field value.
        var likelihood = $row.find('.form-item.likelihood input').val();
        // Check if likelihood is greater than three or less than one and if so
        // reset the field to empty.
        // @todo: Put in some kind of message.
        if (likelihood > 3 || likelihood < 1) {
          $row.find('.form-item.likelihood input').val('');
          likelihood = 0;
        }
        // Calculate the total.
        total = parseFloat(severity * likelihood);
        // If the total isn't zero then update the significance field value.
        if (total != 0) {
          $row.find('.form-item.significance input').val(total);
        }
      });
    }
  }
})(jQuery);
