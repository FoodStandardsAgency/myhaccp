(function($) {

  Drupal.behaviors.parsley_custom = {
    attach: function(context) {
      var form = $('#mforms-wrapper-myhaccp form');
      // Destroy any parsley validation on the form so that we can we enable it
      // on recreation (ajax) of the form. This is needed for the validation to
      // work whenever new items are added or items are removed.
      form.parsley('destroy');
      // Alter the default success and error classes.
      form.parsley(
        {
          successClass: 'success',
          errorClass: 'error',
          focus: 'none',
          trigger: 'change keyup',
          validators: {
            either: function() {
              return {
                validate: function(val, elems, self) {
                  self.options.validateIfUnchanged = true;
                  self.validValue = self.$element.data("value");
                  self.$element.parsley().inEitherProcessing = true;
                  var pass = false;

                  var val = self.$element.val();
                  self.val = val !== "" ? val : self.validValue;

                  elems = elems.split(',');
                  $.each(elems, function(index, elem) {
                    $elem = $(elem);
                    if ($elem.is(':checkbox')) {
                      if ($elem.is(':checked')) {
                        pass = true;
                      }
                    }
                    else {
                      if ($elem.val() != '') {
                        pass = true;
                      }
                    }
                  });

                  self.$element.parsley().inEitherProcessing = false;

                  if (pass == true) {
                    $.each(elems, function(index, elem) {
                      $elem = $(elem);
                      $elem.removeClass('error');
                      $elem.parents('.form-item').removeClass('error');
                      $elem.parents('.form-item').parents('.form-checkboxes').removeClass('error');
                      $elem.parents('.form-item').children('div.validation, ul.parsley-error-list').remove();
                    });
                  }
                  else {
                    $.each(elems, function(index, elem) {
                      $elem = $(elem);
                      $elem.addClass('error');
                      $elem.parents('.form-checkboxes').addClass('error');
                      $elem.parents('.form-item').parents('.form-checkboxes').addClass('error');
                    });
                  }

                  return (pass);
                },
                priority: 2
              };
            }
          },
          messages: {
            multiple: "This value should be a multiple of %s"
          }
        }
      );
      // Add an onFormValidate listener.
      form.parsley('addListener', {
        onFormValidate: function(elem) {
          // Always validate, don't block form submission.
          return true;
        },
        onFieldSuccess: function(elem) {
          // Once field is validated remove the error messages and classes.
          $(elem).parents('.form-item').removeClass('error');
          $(elem).parents('.form-item').parents('.form-checkboxes').removeClass('error');
          $(elem).parents('.form-item').children('div.validation').remove();
        }
      });


    }
  }


})(jQuery);
