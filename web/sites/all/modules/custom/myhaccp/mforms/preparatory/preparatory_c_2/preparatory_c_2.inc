<?php

/**
 * @file
 * Preparatory C 2 stage form and validation handler.
 */

/**
 * Returns keyed array of form labels for C 2 Physical.
 *
 * Helper function to return keyed array of form labels or PDF labels allowing
 * us to render different text in the output PDF document than is rendered when
 * selecting options within the form.
 *
 * This function returns an array for preparatory C2 Q4 (Physical hazards).
 *
 * @param bool $form_options
 *   A boolean to indicate if we want the options to be in a format expected
 *   by Drupal's Form API for checkbox options.
 *
 * @return array
 *   Array of lables with:
 *     ($form_options = TRUE) $key => form label
 *     ($form_options = FALSE)
 *        $key['form_label'] => form label,
 *        $key['pdf_output'] => output for PDF doc.
 */
function preparatory_c_2_physical_get_options($form_options = FALSE) {
  // @ignore comment_comment_eg:function
  $options = array();
  $form_options_array = array();

  $options['metal']['form_label'] = t('Metal');
  $options['metal']['pdf_output'] = t('Metal');

  $options['wood']['form_label'] = t('Wood splinters');
  $options['wood']['pdf_output'] = t('Wood splinters');

  $options['glass']['form_label'] = t('Glass and brittle plastic');
  $options['glass']['pdf_output'] = t('Glass and brittle plastic');

  $options['plastic']['form_label'] = t('Flexible plastic');
  $options['plastic']['pdf_output'] = t('Flexible plastic');

  $options['plasters']['form_label'] = t('Plasters');
  $options['plasters']['pdf_output'] = t('Plasters');

  $options['stones']['form_label'] = t('Stones');
  $options['stones']['pdf_output'] = t('Stones');

  $options['shell']['form_label'] = t('Shell');
  $options['shell']['pdf_output'] = t('Shell');

  $options['fruit']['form_label'] = t('Fruit stones');
  $options['fruit']['pdf_output'] = t('Fruit stones');

  $options['insects']['form_label'] = t('Insects');
  $options['insects']['pdf_output'] = t('Insects');

  $options['paper']['form_label'] = t('Paper/board');
  $options['paper']['pdf_output'] = t('Paper/board');

  $options['hair']['form_label'] = t('Hair');
  $options['hair']['pdf_output'] = t('Hair');

  $options['bones']['form_label'] = t('Bones');
  $options['bones']['pdf_output'] = t('Bones');

  $options['feathers']['form_label'] = t('Feathers');
  $options['feathers']['pdf_output'] = t('Feathers');

  $options['string']['form_label'] = t('String');
  $options['string']['pdf_output'] = t('String');

  $options['nails']['form_label'] = t('Finger nails');
  $options['nails']['pdf_output'] = t('Finger nails');

  $options['pests']['form_label'] = t('Pests');
  $options['pests']['pdf_output'] = t('Pests');

  // If we want the options array formatted for the form builder, reformat array
  // to be appropriate for the form options array.
  if ($form_options) {
    foreach ($options as $key => $option) {
      $form_options_array[$key] = $option['form_label'];
    }
    return $form_options_array;
  }
  else {
    return $options;
  }
}

/**
 * Returns keyed array of form labels for C 2 Chemical.
 *
 * Helper function to return keyed array of form labels or PDF labels allowing
 * us to render different text in the output PDF document than is rendered when
 * selecting options within the form.
 *
 * This function returns an array for preparatory C2 Q4 (Chemical hazards).
 *
 * @param bool $form_options
 *   A boolean to indicate if we want the options to be in a format expected
 *   by Drupal's Form API for checkbox options.
 *
 * @return array
 *   Array of lables with:
 *     ($form_options = TRUE) $key => form label
 *     ($form_options = FALSE)
 *        $key['form_label'] => form label,
 *        $key['pdf_output'] => output for PDF doc.
 */
function preparatory_c_2_chemical_get_options($form_options = FALSE) {
  // @ignore comment_comment_eg:function
  $options = array();
  $form_options_array = array();

  $options['pesticides']['form_label'] = t('Agricultural residues: Pesticides');
  $options['pesticides']['pdf_output'] = t('Agricultural residues: Pesticides');

  $options['phytotoxins']['form_label'] = t('Ingredient dependent Phyto-toxins (plant-based e.g. lectins in kidney beans; cyanogenic glycosides in cassava)');
  $options['phytotoxins']['pdf_output'] = t('Ingredient dependent Phyto-toxins');

  $options['phycotoxins']['form_label'] = t('Ingredient dependent Phyco-toxins (associated with shellfish and certain pelagic fish)');
  $options['phycotoxins']['pdf_output'] = t('Ingredient dependent Phyco-toxins');

  $options['nitrate']['form_label'] = t('Agricultural residues: Nitrate');
  $options['nitrate']['pdf_output'] = t('Agricultural residues: Nitrate');

  $options['drugs']['form_label'] = t('Veterinary Drugs');
  $options['drugs']['pdf_output'] = t('Veterinary Drugs');

  $options['additives']['form_label'] = t('Non-permitted additives (e.g. konjac in children’s confectionery)');
  $options['additives']['pdf_output'] = t('Non-permitted additives');

  $options['heavy_metals']['form_label'] = t('Heavy metals (arsenic, cadmium, lead, mercury)');
  $options['heavy_metals']['pdf_output'] = t('Heavy metals');

  $options['micro_toxins']['form_label'] = t('Other microbiologically produced toxins (e.g. histamine in fish)');
  $options['micro_toxins']['pdf_output'] = t('Other microbiologically produced toxins');

  $options['environmental_contaminants']['form_label'] = t('Environmental contaminants (e.g. dioxins)');
  $options['environmental_contaminants']['pdf_output'] = t('Environmental contaminants');

  $options['process_toxicants']['form_label'] = t('Process toxicants (e.g. acrylamide in high temperature processed carbohydrate rich foods)');
  $options['process_toxicants']['pdf_output'] = t('Process toxicants');

  $options['adulterants']['form_label'] = t('Adulterants (Synthetic colours (e.g. Sudan dyes), melamine, water & sugar (e.g honey))');
  $options['adulterants']['pdf_output'] = t('Adulterants');

  $options['cleaning']['form_label'] = t('Cleaning & sanitising chemicals');
  $options['cleaning']['pdf_output'] = t('Cleaning & sanitising chemicals');

  $options['chemical']['form_label'] = t('Chemical residues migrating from packaging (e.g. plasticisers, BPA)');
  $options['chemical']['pdf_output'] = t('Chemical residues migrating from packaging');

  // If we want the options array formatted for the form builder, reformat array
  // to be appropriate for the form options array.
  if ($form_options) {
    foreach ($options as $key => $option) {
      $form_options_array[$key] = $option['form_label'];
    }
    return $form_options_array;
  }
  else {
    return $options;
  }
}

/**
 * Returns keyed array of form labels for C 2 Biological.
 *
 * Helper function to return keyed array of form labels or PDF labels allowing
 * us to render different text in the output PDF document than is rendered when
 * selecting options within the form.
 *
 * This function returns an array for preparatory C2 Q4 (Biological hazzards).
 *
 * @param bool $form_options
 *   A boolean to indicate if we want the options to be in a format expected
 *   by Drupal's Form API for checkbox options.
 *
 * @return array
 *   Array of lables with:
 *     ($form_options = TRUE) $key => form label
 *     ($form_options = FALSE)
 *        $key['form_label'] => form label,
 *        $key['pdf_output'] => output for PDF doc.
 */
function preparatory_c_2_biological_get_options($form_options = FALSE) {
  // @ignore comment_comment_eg:function
  $options = array();
  $form_options_array = array();

  $options['salmonella']['form_label'] = t('Salmonella');
  $options['salmonella']['pdf_output'] = t('Salmonella');

  $options['listeria']['form_label'] = t('Listeria sp.');
  $options['listeria']['pdf_output'] = t('Listeria sp.');

  $options['escherichia']['form_label'] = t('Escherichia coli');
  $options['escherichia']['pdf_output'] = t('Escherichia coli');

  $options['clortridium']['form_label'] = t('Clostridium botulinum');
  $options['clortridium']['pdf_output'] = t('Clostridium botulinum');

  $options['clorstridia']['form_label'] = t('Clostridia perfringens');
  $options['clorstridia']['pdf_output'] = t('Clostridia perfringens');

  $options['staphylococcus']['form_label'] = t('Staphylococcus aureus');
  $options['staphylococcus']['pdf_output'] = t('Staphylococcus aureus');

  $options['bacillus']['form_label'] = t('Bacillus spp.');
  $options['bacillus']['pdf_output'] = t('Bacillus spp.');

  $options['campylobacter']['form_label'] = t('Campylobacter');
  $options['campylobacter']['pdf_output'] = t('Campylobacter');

  $options['shigella']['form_label'] = t('Shigella');
  $options['shigella']['pdf_output'] = t('Shigella');

  $options['hepatitis']['form_label'] = t('Hepatitis');
  $options['hepatitis']['pdf_output'] = t('Hepatitis');

  $options['cryptosporidium']['form_label'] = t('Cryptosporidium (parasitic protozoa)');
  $options['cryptosporidium']['pdf_output'] = t('Cryptosporidium (parasitic protozoa)');

  $options['psudomonas']['form_label'] = t('Pseudomonas Spp.');
  $options['psudomonas']['pdf_output'] = t('Pseudomonas Spp.');

  $options['norovirus']['form_label'] = t('Norovirus');
  $options['norovirus']['pdf_output'] = t('Norovirus');

  // Note - only correct the spelling in the key if you are sure it will not
  // break existing forms, from experience mforms is brittle, so keeping the
  // key mispelled in favour of correct label for now.
  $options['taxoplasma']['form_label'] = t('Toxoplasma');
  $options['taxoplasma']['pdf_output'] = t('Toxoplasma');

  // If we want the options array formatted for the form builder, reformat array
  // to be appropriate for the form options array.
  if ($form_options) {
    foreach ($options as $key => $option) {
      $form_options_array[$key] = $option['form_label'];
    }
    return $form_options_array;
  }
  else {
    return $options;
  }
}
/**
 * Returns keyed array of form labels for C 2 Allergens.
 *
 * Helper function to return keyed array of form labels or PDF labels allowing
 * us to render different text in the output PDF document than is rendered when
 * selecting options within the form.
 *
 * This function returns an array for preparatory C2 Q4 (Allergens).
 *
 * @param bool $form_options
 *   A boolean to indicate if we want the options to be in a format expected
 *   by Drupal's Form API for checkbox options.
 *
 * @return array
 *   Array of lables with:
 *     ($form_options = TRUE) $key => form label
 *     ($form_options = FALSE)
 *        $key['form_label'] => form label,
 *        $key['pdf_output'] => output for PDF doc.
 */
function preparatory_c_2_allergens_get_options($form_options = FALSE) {
  // @ignore comment_comment_eg:function
  $options = array();
  $form_options_array = array();

  $options['eggs']['form_label'] = t('Eggs and products thereof');
  $options['eggs']['pdf_output'] = t('Eggs');

  $options['milk']['form_label'] = t('Milk and products thereof (including lactose), except: (a) whey used for making alcoholic distillates including ethyl alcohol of agricultural origin (b) lactitol');
  $options['milk']['pdf_output'] = t('Milk');

  $options['fish']['form_label'] = t('Fish and products thereof, except fish gelatine used as carrier for vitamin or carotenoid preparations; fish gelatine or Isinglass used as fining agent in beer and wine.');
  $options['fish']['pdf_output'] = t('Fish');

  $options['sesame']['form_label'] = t('Sesame seeds and products thereof');
  $options['sesame']['pdf_output'] = t('Sesame seeds');

  $options['crustaceans']['form_label'] = t('Crustaceans and products thereof');
  $options['crustaceans']['pdf_output'] = t('Crustaceans');

  $options['peanuts']['form_label'] = t('Peanuts and products thereof');
  $options['peanuts']['pdf_output'] = t('Peanuts');

  $options['cereals']['form_label'] = t('Cereals containing gluten, namely: wheat, rye, barley, oats, spelt, kamut, or their hybridised strains, and products thereof, except: (a) wheat based glucose syrups including dextrose: (b) wheat based maltodextrins; (c) glucose syrups based on barley; (d) cereals used for making alcoholic distillates including ethyl alcohol of agricultural origin.');
  $options['cereals']['pdf_output'] = t('Cereals containing gluten');

  $options['celery']['form_label'] = t('Celery and products thereof');
  $options['celery']['pdf_output'] = t('Celery');

  $options['mustard']['form_label'] = t('Mustard and products thereof');
  $options['mustard']['pdf_output'] = t('Mustard');

  $options['lupin']['form_label'] = t('Lupin and products thereof');
  $options['lupin']['pdf_output'] = t('Lupin');

  $options['soybeans']['form_label'] = t('Soybeans and products thereof, except: (a)fully refined soybean oil and fat (b) natural mixed tocopherols (E306), natural D-alpha tocopherol, natural D-alpha tocopherol acetate, and natural D-alpha tocopherol succinate from soybean sources (c) vegetable oils derived phytosterol esters from soybean sources (d) plant stanol ester produced from vegetable oil sterols from soybean sources');
  $options['soybeans']['pdf_output'] = t('Soybeans');

  $options['molluscs']['form_label'] = t('Molluscs and products thereof');
  $options['molluscs']['pdf_output'] = t('Molluscs');

  $options['sulphur']['form_label'] = t('Sulphur dioxide and sulphites at concentrations of more than 10mg/kg or 10mg/litre in terms of the total SO2 which are to be calculated for products as proposed ready for consumption or as reconstituted according to the instructions of the manufacturers');
  $options['sulphur']['pdf_output'] = t('Sulphur dioxide and sulphites');

  $options['nuts']['form_label'] = t('Nuts, namely: almonds, hazelnuts,walnuts,cashewnuts, pecan nuts, Brazil nuts, pistachio nuts, macadamia or Queensland nuts and products thereof, except for nuts used for making alcoholic distillates including ethyl alcohol of agricultural origin.');
  $options['nuts']['pdf_output'] = t('Nuts');

  // If we want the options array formatted for the form builder, reformat array
  // to be appropriate for the form options array.
  if ($form_options) {
    foreach ($options as $key => $option) {
      $form_options_array[$key] = $option['form_label'];
    }
    return $form_options_array;
  }
  else {
    return $options;
  }
}

/**
 * Preparatory C 2.
 */
function preparatory_c_2(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_d';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_c_2');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-c-2';

  // Show global message on this form.
  $form['validation_messages']['#attributes']['data-validation-stage'] = 'preparatory_c_2';

  // Wrap the form section in a fieldset.
  $form['preparatory_c_2'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  $form['preparatory_c_2']['wrapper_title'] = array(
    '#markup' => '<div class="label">' . t('4. What hazards will the HACCP plan cover? !tip !help', array(
        '!tip' => _help_tip(),
        '!help' => '<div class="help-text">' . t("State which hazards will be considered in the HACCP plan (i.e. Biological, Physical, Chemical, Allergens). !link", array(
            '!link' => myhaccp_prepare_more_link(15),
          )) . '</div>',
    )) . '</div>',

  );

  // Physical hazards.
  $form['preparatory_c_2']['wrapper']['physical_c_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  // Get the physical options array from the helper function.
  $preparatory_c_2_physical_options = preparatory_c_2_physical_get_options($form_options = TRUE);

  $form['preparatory_c_2']['wrapper']['physical_c_4']['physical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Physical'),
    '#options' => $preparatory_c_2_physical_options,
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.physical_c_4.physical', array()),
  );

  $form['preparatory_c_2']['wrapper']['physical_c_4']['physical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.physical_c_4.physical_other', FALSE),
  );

  // Chemical.
  $form['preparatory_c_2']['wrapper']['chemical_c_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'chemical',
    ),
  );

  // Get the options
  $preparatory_c_2_chemical_options = preparatory_c_2_chemical_get_options($form_options = TRUE);

  $form['preparatory_c_2']['wrapper']['chemical_c_4']['chemical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Chemical'),
    '#options' => $preparatory_c_2_chemical_options,
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.chemical_c_4.chemical', array()),
  );

  $form['preparatory_c_2']['wrapper']['chemical_c_4']['chemical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.chemical_c_4.chemical_other', FALSE),
  );

  // Biological.
  $form['preparatory_c_2']['wrapper']['biological_c_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'biological',
    ),
  );

  // Get the form options.
  $preparatory_c_2_biological_options = preparatory_c_2_biological_get_options($form_options = TRUE);

  $form['preparatory_c_2']['wrapper']['biological_c_4']['biological'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Biological'),
    '#options' => $preparatory_c_2_biological_options,
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.biological_c_4.biological', array()),
  );

  $form['preparatory_c_2']['wrapper']['biological_c_4']['biological_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.biological_c_4.biological_other', FALSE),
  );

  // Allergens.
  $form['preparatory_c_2']['wrapper']['allergens_c_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'allergens',
    ),
  );
  $preparatory_c_2_allergens_options = preparatory_c_2_allergens_get_options($form_options = TRUE);
  $form['preparatory_c_2']['wrapper']['allergens_c_4']['allergens'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allergens'),
    '#options' => $preparatory_c_2_allergens_options,
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.allergens_c_4.allergens', array()),
  );

  $form['preparatory_c_2']['wrapper']['allergens_c_4']['allergens_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.allergens_c_4.allergens_other', FALSE),
  );

  // Adding new option "Provide details of any documents or information that
  // you have used in your HACCP plan.
  // Placing this in an additional wrapper to maintain the presentation in line
  // with the previous questions.
  $form['preparatory_c_2']['wrapper']['c_5'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Question definition.
  $form['preparatory_c_2']['wrapper']['c_5']['question'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('5. Provide details of any documents or information that you have used in your HACCP plan.'),
    '#help_text' => t("State any documentation or sources of information used in your HACCP plan e.g.
FSA Guidance for food business operators on Microbiological criteria for foodstuffs."),
    // @todo - we will need to add new help text and ensure this links to the correct place.
    '#help_link' => 15,
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.c_5.question', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'false',
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_2_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  // Validation: Some content.
  $checks = array(
    'preparatory_c_2.wrapper.physical_c_4.physical' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.chemical_c_4.chemical' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.biological_c_4.biological' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.allergens_c_4.allergens' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.physical_c_4.physical_other' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.chemical_c_4.chemical_other' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.biological_c_4.biological_other' => 'fieldIsNotEmpty',
    'preparatory_c_2.wrapper.allergens_c_4.allergens_other' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validation = new Validation($form, $form_state, $target);
    $results[] = $validation->$method();
  }

  // The new method of checking if all fields are empty renders any checks
  // useless so we're not doing anything else here.
  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
