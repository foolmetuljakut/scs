#include "ExplosiveDamageCalculator.hpp"

namespace src::combat {

void ExplosiveDamageCalculator::execute_attack() {
  float damage_normal = calculate_damage_over_distance();
  apply_damage(damage_normal);
}

void ExplosiveDamageCalculator::apply_damage(decltype(src::unit::UnitParams::_base_damage_normal) incoming) {

  if (incoming > 0) {
    // reduce incoming damage through a pipeline of accounting different effects
    float normal_with_ducking_cover = calculate_damage_through_ducking(incoming);
    float normal_with_ducking_cover_camo = calculate_damage_through_camo(normal_with_ducking_cover);

    target_unit->apply_damage(normal_with_ducking_cover_camo);
    target_unit->apply_morale_damage(normal_with_ducking_cover_camo);
  }
}

float ExplosiveDamageCalculator::calculate_damage_over_distance() {

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

float ExplosiveDamageCalculator::calculate_damage_through_ducking(
  decltype(src::unit::UnitParams::_base_damage_normal) incoming) {

    float modified_normal = incoming;

    if(target_unit->ducked()) {
      modified_normal *= terrain._ducking_factor;
    }

    return modified_normal;
}

float ExplosiveDamageCalculator::calculate_damage_through_camo(decltype(src::unit::UnitParams::_base_damage_normal) incoming) {

    float modified_normal = incoming;

    if(target_unit->camo() != src::unit::CamoType::Normal && 
        target_unit->camo() == terrain._terrain_type) {
      modified_normal *= terrain._camo_factor;
    }

    return modified_normal;
}


};