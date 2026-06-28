#include "NormalDamageCalculator.hpp"

namespace src::combat {

void NormalDamageCalculator::execute_attack() {
  float damage_normal = calculate_damage_over_distance();
  apply_damage(damage_normal);
}

void NormalDamageCalculator::apply_damage(decltype(src::unit::UnitParams::_base_damage_normal) incoming) {

  if (incoming > 0) {
    // reduce incoming damage through a pipeline of accounting different effects
    float normal_with_ducking_cover = calculate_damage_through_cover_and_ducking(incoming);
    float normal_with_ducking_cover_camo = calculate_damage_through_camo(normal_with_ducking_cover);

    target_unit->apply_damage(normal_with_ducking_cover_camo);
    target_unit->apply_morale_damage(normal_with_ducking_cover_camo, incoming - normal_with_ducking_cover_camo);
  }
}

float NormalDamageCalculator::calculate_damage_over_distance() {

  // one unit will always start at their supposedly higher effectivy range, while the other has to work with that
  float distance = std::max(
    std::min(terrain._max_distance, acting_unit->effective_range()),
    std::min(terrain._max_distance, target_unit->effective_range())
  );

  float drop_off_probability = 1.f;
  if(distance > 0) {
    drop_off_probability = std::min(
      0.5f * acting_unit->effective_range() / distance,
      1.f
    );
  }

  float damage_normal = acting_unit->damage_normal() * drop_off_probability;
  return damage_normal;
}

float NormalDamageCalculator::calculate_damage_through_cover_and_ducking(
  decltype(src::unit::UnitParams::_base_damage_normal) incoming) {
  
    // basic idea: troops will fire at uncovered troops first (easy to pick off)
    //  troops are divided into covered / uncovered troops - covered take only 0.244*incoming damage
    //  incoming normal damage is divided between, prioritizing uncovered troops 

    // units that are dug in count as covered, even if the terrain doesn't provide cover
    int _effective_cover_provision = target_unit->dug_in() ? target_unit->alive() : terrain._cover_provision;

    int target_troops_covered = std::min(target_unit->alive(), _effective_cover_provision),
        target_troops_uncovered = target_unit->alive() - target_troops_covered;

    float uncovered_normal = std::min(
      static_cast<float>(target_troops_uncovered),
      incoming
    ); // assign as much as possible to uncovered units

    float covered_remaining = std::min(
      static_cast<float>(target_troops_covered),
      terrain._cover_factor * (incoming - uncovered_normal)
    ); // assign "left over" damage to covered units

    if(target_unit->ducked()) {
      uncovered_normal *= terrain._ducking_factor;
    } // additionally, those not in cover can lay down and duck

    float modified_normal = uncovered_normal + covered_remaining;
    return modified_normal;
}

float NormalDamageCalculator::calculate_damage_through_camo(decltype(src::unit::UnitParams::_base_damage_normal) incoming) {

    float modified_normal = incoming;

    if(target_unit->camo() != src::unit::CamoType::Normal && 
        target_unit->camo() == terrain._terrain_type) {
      modified_normal *= terrain._camo_factor;
    }

    return modified_normal;
}


};