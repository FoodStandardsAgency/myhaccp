<?php

function preparatory_c_2_chemicals_get_options ($form_options = FALSE) {

  $options = array();
  $form_options_array = array();
    
  $options['mycotoxins']['form_label'] = t('Ingredient dependent Mycotoxins (e.g. deoxynivalenol in cereals; patulin in apples)');
  $options['mycotoxins']['pdf_output'] = t('Ingredient dependent Mycotoxins');

  $options['phytotoxins']['form_label'] = t('Ingredient dependent Phyto-toxins (plant-based e.g. lectins in kidney beans; cyanogenic glycosides in cassava)');
  $options['phytotoxins']['pdf_output'] = t('Ingredient dependent Phyto-toxins');
    
  $options['phycotoxins']['form_label'] = t('Ingredient dependent Phyco-toxins (associated with shellfish and certain pelagic fish)');
  $options['phycotoxins']['pdf_output'] = t('Ingredient dependent Phyco-toxins');
  
  $options['pesticides']['form_label'] = t('Agricultural residues: Pesticides)');
  $options['pesticides']['pdf_output'] = t('Agricultural residues: Pesticides)');
  
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
  } else {
    return $options;
  }
}





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
  global $container;
  // Get the current study.
  $study = $container['study'];
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
          )) . '</div>'
    )) . '</div>',

  );

  // Physical hazards.

  $form['preparatory_c_2']['wrapper']['physical_c_4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['preparatory_c_2']['wrapper']['physical_c_4']['physical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Physical'),
    '#options' => array(
      'metal' => t('Metal'),
      'wood' => t('Wood splinters'),
      'glass' => t('Glass and brittle plastic'),
      'plastic' => t('Flexible plastic'),
      'plasters' => t('Plasters'),
      'stones' => t('Stones'),
      'shell' => t('Shell'),
      'fruit' => t('Fruit stones'),
      'insects' => t('Insects'),
      'paper' => t('Paper/board'),
      'hair' => t('Hair'),
      'bones' => t('Bones'),
      'feathers' => t('Feathers'),
      'string' => t('String'),
      'nails' => t('Finger nails'),
      'pests' => t('Pests'),
    ),
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
  $chemical_c_4_options = preparatory_c_2_chemicals_get_options ($form_options = TRUE);
  
  
  $form['preparatory_c_2']['wrapper']['chemical_c_4']['chemical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Chemical'),
    '#options' => $chemical_c_4_options,
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

  $form['preparatory_c_2']['wrapper']['biological_c_4']['biological'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Biological'),
    '#options' => array(
      'salmonella' => t('Salmonella'),
      'listeria' => t('Listeria sp.'),
      'escherichia' => t('Escherichia coli'),
      'clortridium' => t('Clostridium botulinum'),
      'clorstridia' => t('Clostridia perfringens'),
      'staphylococcus' => t('Staphylococcus aureus'),
      'bacillus' => t('Bacillus spp.'),
      'campylobacter' => t('Campylobacter'),
      'shigella' => t('Shigella'),
      'hepatitis' => t('Hepatitis'),
      'cryptosporidium' => t('Cryptosporidium (parasitic protozoa)'),
      'psudomonas' => t('Pseudomonas Spp.'),
      'hepatitis' => t('Hepatitis'),
      'norovirus' => t('Norovirus'),
      'taxoplasma' => t('Toxoplasma'),
    ),
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

  $form['preparatory_c_2']['wrapper']['allergens_c_4']['allergens'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allergens'),
    '#options' => array(
      'eggs' => t('Eggs and products thereof'),
      'milk' => t('Milk and products thereof (including lactose), except: (a) whey used for making alcoholic distillates including ethyl alcohol of agricultural origin (b) lactitol'),
      'fish' => t('Fish and products thereof, except fish gelatine used as carrier for vitamin or carotenoid preparations; fish gelatine or Isinglass used as fining agent in beer and wine.'),
      'sesame' => t('Sesame seeds and products thereof'),
      'crustaceans' => t('Crustaceans and products thereof'),
      'peanuts' => t('Peanuts and products thereof'),
      'cereals' => t('Cereals containing gluten, namely: wheat, rye, barley, oats, spelt, kamut, or their hybridised strains, and products thereof, except: (a) wheat based glucose syrups including dextrose: (b) wheat based maltodextrins; (c) glucose syrups based on barley; (d) cereals used for making alcoholic distillates including ethyl alcohol of agricultural origin.'),
      'celery' => t('Celery and products thereof'),
      'mustard' => t('Mustard and products thereof'),
      'lupin' => t('Lupin and products thereof'),
      'soybeans' => t('Soybeans and products thereof, except: (a)fully refined soybean oil and fat (b) natural mixed tocopherols (E306), natural D-alpha tocopherol, natural D-alpha tocopherol acetate, and natural D-alpha tocopherol succinate from soybean sources (c) vegetable oils derived phytosterol esters from soybean sources (d) plant stanol ester produced from vegetable oil sterols from soybean sources'),
      'molluscs' => t('Molluscs and products thereof'),
      'sulphur' => t('Sulphur dioxide and sulphites at concentrations of more than 10mg/kg or 10mg/litre in terms of the total SO2 which are to be calculated for products as proposed ready for consumption or as reconstituted according to the instructions of the manufacturers'),
      'nuts' => t('Nuts, namely: almonds, hazelnuts,walnuts,cashewnuts, pecan nuts, Brazil nuts, pistachio nuts, macadamia or Queensland nuts and products thereof, except for nuts used for making alcoholic distillates including ethyl alcohol of agricultural origin.'),
    ),
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.allergens_c_4.allergens', array()),
  );

  $form['preparatory_c_2']['wrapper']['allergens_c_4']['allergens_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'preparatory_c_2.wrapper.allergens_c_4.allergens_other', FALSE),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_2_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
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
