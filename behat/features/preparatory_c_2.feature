@api
Feature: Preparatory C.2
  In order to complete Preparatory C.2
  As an authenticated user
  I need to be able to complete stage C.2

  Background: Begin a study
    Given I am logged in as a user with the "authenticated user" role
    And I visit "/tool/study/create"
    And I press the "C.2" button

  Scenario: Complete Preparatory C.2 and confirm data entry

    #Physical checkboxes
    Given I check "Metal"
    And I check "Wood splinters"
    And I check "Glass and brittle plastic"
    And I check "Flexible plastic"
    And I check "Plasters"
    And I check "Stones"
    And I check "Shell"
    And I check "Fruit stones"
    And I check "Insects"
    And I check "Paper/board"
    And I check "Hair"
    And I check "Bones"
    And I check "Feathers"
    And I check "String"
    And I check "Finger nails"
    And I check "Pests"
    And I fill in "Other" with "rocks"

    # Chemical checkboxes
    And I check "Agricultural residues: Pesticides"
    And I check "Ingredient dependent Phyto-toxins (plant-based e.g. lectins in kidney beans; cyanogenic glycosides in cassava)"
    And I check "Ingredient dependent Phyco-toxins (associated with shellfish and certain pelagic fish)"
    And I check "Agricultural residues: Nitrate"
    And I check "Veterinary Drugs"
    And I check "Non-permitted additives (e.g. konjac in children’s confectionery)"
    And I check "Heavy metals (arsenic, cadmium, lead, mercury)"
    And I check "Other microbiologically produced toxins (e.g. histamine in fish)"
    And I check "Environmental contaminants (e.g. dioxins)"
    And I check "Process toxicants (e.g. acrylamide in high temperature processed carbohydrate rich foods)"
    And I check "Adulterants (Synthetic colours (e.g. Sudan dyes), melamine, water & sugar (e.g honey))"
    And I check "Cleaning & sanitising chemicals"
    And I check "Chemical residues migrating from packaging (e.g. plasticisers, BPA)"

    # Biological checkboxes
    And I check "Salmonella"
    And I check "Listeria sp."
    And I check "Escherichia coli"
    And I check "Clostridium botulinum"
    And I check "Clostridia perfringens"
    And I check "Staphylococcus aureus"
    And I check "Bacillus spp."
    And I check "Campylobacter"
    And I check "Shigella"
    And I check "Hepatitis"
    And I check "Cryptosporidium (parasitic protozoa)"
    And I check "Pseudomonas Spp."
    And I check "Norovirus"
    And I check "Toxoplasma"

    # Allergens checkboxes

    And I check "Eggs and products thereof"
    And I check "Milk and products thereof (including lactose), except: (a) whey used for making alcoholic distillates including ethyl alcohol of agricultural origin (b) lactitol"
   And I check "Fish and products thereof, except fish gelatine used as carrier for vitamin or carotenoid preparations; fish gelatine or Isinglass used as fining agent in beer and wine."
    And I check "Sesame seeds and products thereof"
    And I check "Crustaceans and products thereof"
    And I check "Peanuts and products thereof"
    And I check "Cereals containing gluten, namely: wheat, rye, barley, oats, spelt, kamut, or their hybridised strains, and products thereof, except: (a) wheat based glucose syrups including dextrose: (b) wheat based maltodextrins; (c) glucose syrups based on barley; (d) cereals used for making alcoholic distillates including ethyl alcohol of agricultural origin."
    And I check "Celery and products thereof"
    And I check "Mustard and products thereof"
    And I check "Lupin and products thereof"
    And I check "Soybeans and products thereof, except: (a)fully refined soybean oil and fat (b) natural mixed tocopherols (E306), natural D-alpha tocopherol, natural D-alpha tocopherol acetate, and natural D-alpha tocopherol succinate from soybean sources (c) vegetable oils derived phytosterol esters from soybean sources (d) plant stanol ester produced from vegetable oil sterols from soybean sources"
    And I check "Molluscs and products thereof"
    And I check "Sulphur dioxide and sulphites at concentrations of more than 10mg/kg or 10mg/litre in terms of the total SO2 which are to be calculated for products as proposed ready for consumption or as reconstituted according to the instructions of the manufacturers"
    And I check "Nuts, namely: almonds, hazelnuts,walnuts,cashewnuts, pecan nuts, Brazil nuts, pistachio nuts, macadamia or Queensland nuts and products thereof, except for nuts used for making alcoholic distillates including ethyl alcohol of agricultural origin."

    # Save the page
    When I press the "Save this page" button

    # Confirm the checkboxes are checked

    # Physical checkboxes
    And the "Metal" checkbox should be checked
    And the "Glass and brittle plastic" checkbox should be checked
    And the "Flexible plastic" checkbox should be checked
    And the "Plasters" checkbox should be checked
    And the "Stones" checkbox should be checked
    And the "Shell" checkbox should be checked
    And the "Fruit stones" checkbox should be checked
    And the "Insects" checkbox should be checked
    And the "Paper/board" checkbox should be checked
    And the "Hair" checkbox should be checked
    And the "Bones" checkbox should be checked
    And the "Feathers" checkbox should be checked
    And the "String" checkbox should be checked
    And the "Finger nails" checkbox should be checked
    And the "Pests" checkbox should be checked
    And the "Other" field should contain "rocks"

    # Chemical checkboxes
    And the "Agricultural residues: Pesticides" checkbox should be checked
    And the "Ingredient dependent Phyto-toxins (plant-based e.g. lectins in kidney beans; cyanogenic glycosides in cassava)" checkbox should be checked
    And the "Ingredient dependent Phyco-toxins (associated with shellfish and certain pelagic fish)" checkbox should be checked
    And the "Agricultural residues: Nitrate" checkbox should be checked
    And the "Veterinary Drugs" checkbox should be checked
    And the "Non-permitted additives (e.g. konjac in children’s confectionery)" checkbox should be checked
    And the "Heavy metals (arsenic, cadmium, lead, mercury)" checkbox should be checked
    And the "Other microbiologically produced toxins (e.g. histamine in fish)" checkbox should be checked
    And the "Environmental contaminants (e.g. dioxins)" checkbox should be checked
    And the "Process toxicants (e.g. acrylamide in high temperature processed carbohydrate rich foods)" checkbox should be checked
    And the "Adulterants (Synthetic colours (e.g. Sudan dyes), melamine, water & sugar (e.g honey))" checkbox should be checked
    And the "Cleaning & sanitising chemicals" checkbox should be checked
    And the "Chemical residues migrating from packaging (e.g. plasticisers, BPA)" checkbox should be checked

# Biological checkboxes
    And the "Salmonella" checkbox should be checked
    And the "Listeria sp." checkbox should be checked
    And the "Escherichia coli" checkbox should be checked
    And the "Clostridium botulinum" checkbox should be checked
    And the "Clostridia perfringens" checkbox should be checked
    And the "Staphylococcus aureus" checkbox should be checked
    And the "Bacillus spp." checkbox should be checked
    And the "Campylobacter" checkbox should be checked
    And the "Shigella" checkbox should be checked
    And the "Hepatitis" checkbox should be checked
    And the "Cryptosporidium (parasitic protozoa)" checkbox should be checked
    And the "Pseudomonas Spp." checkbox should be checked
    And the "Norovirus" checkbox should be checked
    And the "Toxoplasma" checkbox should be checked

    # Allergens checkboxes

    And the "Eggs and products thereof" checkbox should be checked
    And the "Milk and products thereof (including lactose), except: (a) whey used for making alcoholic distillates including ethyl alcohol of agricultural origin (b) lactitol" checkbox should be checked
   And the "Fish and products thereof, except fish gelatine used as carrier for vitamin or carotenoid preparations; fish gelatine or Isinglass used as fining agent in beer and wine." checkbox should be checked
    And the "Sesame seeds and products thereof" checkbox should be checked
    And the "Crustaceans and products thereof" checkbox should be checked
    And the "Peanuts and products thereof" checkbox should be checked
    And the "Cereals containing gluten, namely: wheat, rye, barley, oats, spelt, kamut, or their hybridised strains, and products thereof, except: (a) wheat based glucose syrups including dextrose: (b) wheat based maltodextrins; (c) glucose syrups based on barley; (d) cereals used for making alcoholic distillates including ethyl alcohol of agricultural origin." checkbox should be checked
    And the "Celery and products thereof" checkbox should be checked
    And the "Mustard and products thereof" checkbox should be checked
    And the "Lupin and products thereof" checkbox should be checked
    And the "Soybeans and products thereof, except: (a)fully refined soybean oil and fat (b) natural mixed tocopherols (E306), natural D-alpha tocopherol, natural D-alpha tocopherol acetate, and natural D-alpha tocopherol succinate from soybean sources (c) vegetable oils derived phytosterol esters from soybean sources (d) plant stanol ester produced from vegetable oil sterols from soybean sources" checkbox should be checked
    And the "Molluscs and products thereof" checkbox should be checked
    And the "Sulphur dioxide and sulphites at concentrations of more than 10mg/kg or 10mg/litre in terms of the total SO2 which are to be calculated for products as proposed ready for consumption or as reconstituted according to the instructions of the manufacturers" checkbox should be checked
    And the "Nuts, namely: almonds, hazelnuts,walnuts,cashewnuts, pecan nuts, Brazil nuts, pistachio nuts, macadamia or Queensland nuts and products thereof, except for nuts used for making alcoholic distillates including ethyl alcohol of agricultural origin." checkbox should be checked

