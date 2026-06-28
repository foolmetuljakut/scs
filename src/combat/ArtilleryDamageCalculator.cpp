#include "ArtilleryDamageCalculator.hpp"

namespace src::combat {

void ArtilleryDamageCalculator::execute_attack() {
  float damage_normal = calculate_damage();
  apply_damage(damage_normal);
}

void ArtilleryDamageCalculator::apply_damage(decltype(src::unit::UnitParams::_base_damage_normal) incoming) {

  if (incoming > 0) {
    // reduce incoming damage through a pipeline of accounting different effects
    float normal_with_cover = calculate_damage_through_cover(incoming);

    target_unit->apply_damage(normal_with_cover);
    target_unit->apply_morale_damage(normal_with_cover, incoming - normal_with_cover);
  }
}

float ArtilleryDamageCalculator::calculate_damage() {
  return acting_unit->damage_normal();
}

float ArtilleryDamageCalculator::calculate_damage_through_cover(
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

    float modified_normal = uncovered_normal + covered_remaining;
    return modified_normal;
}

};