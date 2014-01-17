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
            notequal: function(val, elem) {
              return {
                validate: function(val, elems, self) {
                  console.log(val);
                  console.log(elems);
                  val !== $(elems).val()
                }
              };
            },
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
            notEqual: "This value should not be the same."
          },
          errors: {
            classHandler: function(elem, isRadioOrCheckbox) {
              // If this is a radio button or a checkbox then step up a couple
              // of parents in the DOM to reach the wrapper.
              if (isRadioOrCheckbox) {
                // Handle checkbox elements.
                if ($(elem).parent().hasClass('form-type-checkbox')) {
                  if ($(elem).parents('.form-checkboxes').length > 0) {
                    // Handle multiple checkboxes.
                    return $(elem).parent().parent();
                  }
                  else {
                    // Handle a single checkbox.
                    return $(elem).parent();
                  }
                }
                else {
                  // Radios.
                  return $(elem).parent().parent();
                }
              }
              else {
                // Standard.
                return $(elem);
              }
            }
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
          $(elem).parents('.form-item').parents('.form-checkboxes, .form-radios').removeClass('error').children('.form-checkbox, .form-radio').removeClass('error');
          $(elem).parents('.form-item').children('ul.parsley-error-list').remove();
        },
        onFieldError: function(elem) {
          // Remove and server side error messages.
          $(elem).parents('.form-item').children('ul.parsley-error-list.server-side').remove();
//          $(elem).parents('.form-item').parents('.form-checkboxes, .form-radios').addClass('error');
        }
      });

      // Every time one of the submit button is clicked we want to destroy
      // parsley. This is needed for Chrome which displays the parsley messages
      // despite the onFormValidate handler returning TRUE.
      $('[type="submit"]').click(function() {
        form.parsley('destroy');
      });

    }
  }


})(jQuery);
