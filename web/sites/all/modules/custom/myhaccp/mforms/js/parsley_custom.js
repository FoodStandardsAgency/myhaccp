(function($) {

  Drupal.behaviors.parsley_custom = {
    attach: function(context) {
      var form = $('#mforms-wrapper-myhaccp form');
      // Alter the default success and error classes.
      form.parsley(
        {
          successClass: 'success',
          errorClass: 'error',
          focus: 'none'
        }
      );
      // Add a onFormValidate listener.
      form.parsley('addListener', {
        onFormValidate: function(elem) {
          // Always validate, don't block form submission.
          return true;
        },
        onFieldSuccess: function(elem) {
          // Once field is validated remove the error messages.
          $(elem).parents('.form-item').children('div.validation').hide();
        }
      });
    }
  }
})(jQuery);
