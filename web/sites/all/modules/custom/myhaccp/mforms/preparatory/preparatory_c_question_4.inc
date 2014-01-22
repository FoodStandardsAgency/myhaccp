<?php

function preparatory_c_question_4(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_d';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_c_question_4');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage C: Define scope of the study, <br/>Question 4', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-c-2';

  // Show global message on this form.
  $form['validation_messages'] = array(
    '#type' => 'container',
    '#id' => 'validation-messages',
    '#weight' => -10,
    '#attributes' => array(
      'data-validation-stage' => 'preparatory_c_question_4',
    ),
  );

  // Wrap the form section in a fieldset.
  $form['preparatory_c_question_4'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['preparatory_c_question_4']['wrapper_title'] = array(
    '#markup' => '<div class="label">' . t('4. What hazards will the HACCP plan cover? !tip', array(
      '!tip' => _help_tip(),
    )) . '</div>',
  );

  // Physical hazards.

  $form['preparatory_c_question_4']['wrapper']['physical_preparatory_c_question_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['preparatory_c_question_4']['wrapper']['physical_preparatory_c_question_4']['physical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Physical'),
    '#options' => drupal_map_assoc(
      array(
        t('Metal'),
        t('Wood splinters'),
        t('Glass and brittle plastic'),
        t('Flexible plastic'),
        t('Plasters'),
        t('Stones'),
        t('Shell'),
        t('Fruit stones'),
        t('Insects'),
        t('Paper/board'),
        t('Hair'),
        t('Bones'),
        t('Feathers'),
        t('String'),
        t('Finger nails'),
        t('Pests'),
      )
    ),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.physical_preparatory_c_question_4.physical', array()),
  );

  $form['preparatory_c_question_4']['wrapper']['physical_preparatory_c_question_4']['physical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.physical_preparatory_c_question_4.physical_other', FALSE),
  );

  // Chemical.

  $form['preparatory_c_question_4']['wrapper']['chemical_preparatory_c_question_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'chemical',
    ),
  );

  $form['preparatory_c_question_4']['wrapper']['chemical_preparatory_c_question_4']['chemical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Chemical'),
    '#options' => drupal_map_assoc(
      array(
        t('Ingredient dependent Mycotoxins (e.g. deoxynivalenol in cereals; patulin in apples)'),
        t('Ingredient dependent Phyto-toxins (plant-based e.g. lectins in kidney beans; cyanogenic glycosides in cassava)'),
        t('Ingredient dependent Phyco-toxins (associated with shellfish and certain pelagic fish)'),
        t('Agricultural residues: Pesticides'),
        t('Agricultural residues: Nitrate'),
        t('Veterinary Drugs'),
        t('Non-permitted additives (e.g. konjac in children’s confectionery)'),
        t('Heavy metals (arsenic, cadmium, lead, mercury)'),
        t('Other microbiologically produced toxins (e.g. histamine in fish)'),
        t('Environmental contaminants (e.g. dioxins)'),
        t('Process toxicants (e.g. acrylamide in hig temeperature processed carbohydrate rich foods)'),
        t('Adulterants (Synthetic colours (e.g. Sudan dyes), melamine, water & sugar (e.g honey))'),
        t('Cleaning & sanitising chemicals'),
        t('Chemical residues migrating from packaging (e.g. plasticisers, BPA)'),
      )
    ),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.chemical_preparatory_c_question_4.chemical', array()),
  );

  $form['preparatory_c_question_4']['wrapper']['chemical_preparatory_c_question_4']['chemical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.chemical_preparatory_c_question_4.chemical_other', FALSE),
  );

  // Biological.

  $form['preparatory_c_question_4']['wrapper']['biological_preparatory_c_question_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'biological',
    ),
  );

  $form['preparatory_c_question_4']['wrapper']['biological_preparatory_c_question_4']['biological'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Biological'),
    '#options' => array_flip(drupal_map_assoc(array(
        t('Salmonella '),
        t('Listeria sp.'),
        t('Escherichia coli '),
        t('Clostridium botulinum'),
        t('Clostridia perfringens '),
        t('Staphylococcus aureus '),
        t('Bacillus spp.'),
        t('Campylobacter'),
        t('Shigella'),
        t('Hepatitis'),
        t('Cryptosporidium (parasitic protozoa)'),
        t('Psudomonas Spp.'),
        t('Hepatitis'),
        t('Norovirus'),
        t('Toxoplasma'),
      ), 'drupal_html_id')
    ),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.biological_preparatory_c_question_4.biological', array()),
  );

  $form['preparatory_c_question_4']['wrapper']['biological_preparatory_c_question_4']['biological_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.biological_preparatory_c_question_4.biological_other', FALSE),
  );

  // Allergens.

  $form['preparatory_c_question_4']['wrapper']['allergens_preparatory_c_question_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'allergens',
    ),
  );

  $form['preparatory_c_question_4']['wrapper']['allergens_preparatory_c_question_4']['allergens'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allergens'),
    '#options' => drupal_map_assoc(
      array(
        t('Eggs and products there of'),
        t('Milk and products thereof (including lactose), except: (a) whey used for making alcoholic distillates including ethyl alcohol of agricultural origin (b) lactitol'),
        t('Fish and products there of, except fish gelatine used as carrier for vitamin or carotenoid preparations; fish gelatine or Isinglass used as fining agent in beer and wine.'),
        t('Sesame seeds and products thereof'),
        t('Crustaceans and products there of '),
        t('Peanuts and products thereof'),
        t('Cereals containing gluten, namely: wheat, rye, barley, oats, spelt, kamut, or their hybridised strains, and products thereof, except: (a) wheat based glucose syrups including dextrose: (b) wheat based maltodextrins; (c) glucose syrups based on barley; (d) cereals used for making alcoholic distillates including ethyl alcohol of agricultural origin.'),
        t('Celery and products thereof'),
        t('Mustard and products thereof'),
        t('Lupin and products thereof'),
        t('Soybeans and products thereof, except: (a)fully refined soybean oil and fat (b) natural mixed tocopherols (E306), natural D-alpha tocopherol, natural D-alpha tocopherol acetate, and natural D-alpha tocopherol succinate from soybean sources (c) vegetable oils derived phytosterol esters from soybean sources (d) plant stanol ester produced from vegetable oil sterols from soybean sources'),
        t('Molluscs and products thereof'),
        t('Sulphur dioxide and sulphites at concentrations of more than 10mg/kg or 10mg/litre in terms of the total SO2 which are to be calculated for products as proposed ready for consumption or as reconstituted according to the instructions of the manufacturers'),
        t('Nuts, namely: almonds, hazelnuts,walnuts,cashewnuts, pecan nuts, Brazil nuts, pistachio nuts, macadamia or Queensland nuts and products thereof, except for nuts used for making alcoholic distillates including ethyl alcohol of agricultural origin.'),
      )
    ),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.allergens_preparatory_c_question_4.allergens', array()),
  );

  $form['preparatory_c_question_4']['wrapper']['allergens_preparatory_c_question_4']['allergens_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_question_4.wrapper.allergens_preparatory_c_question_4.allergens_other', FALSE),
  );

  $form['#validate'][] = 'preparatory_c_question_4_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_question_4_validate($form, &$form_state) {
  $invalid = array();

  // Validation: Some content.
  $checks = array(
    'preparatory_c_question_4.wrapper.physical_preparatory_c_question_4.physical' => '_checkboxes_field_is_empty',
    'preparatory_c_question_4.wrapper.chemical_preparatory_c_question_4.chemical' => '_checkboxes_field_is_empty',
    'preparatory_c_question_4.wrapper.biological_preparatory_c_question_4.biological' => '_checkboxes_field_is_empty',
    'preparatory_c_question_4.wrapper.allergens_preparatory_c_question_4.allergens' => '_checkboxes_field_is_empty',
    'preparatory_c_question_4.wrapper.physical_preparatory_c_question_4.physical_other' => '_text_field_is_empty',
    'preparatory_c_question_4.wrapper.chemical_preparatory_c_question_4.chemical_other' => '_text_field_is_empty',
    'preparatory_c_question_4.wrapper.biological_preparatory_c_question_4.biological_other' => '_text_field_is_empty',
    'preparatory_c_question_4.wrapper.allergens_preparatory_c_question_4.allergens_other' => '_text_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state, TRUE);
  }

  if (!in_array(FALSE, $invalid)) {
    $message = t('Please add some content.');
    myhacpp_prepare_validation('global', array('preparatory_c_question_4' => $message), $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
