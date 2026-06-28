#pragma once
#include "IDamageCalculator.hpp"

namespace src::combat {

class NormalDamageCalculator : public IDamageCalculator {

public:
    NormalDamageCalculator(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain)
        : IDamageCalculator(acting_unit, target_unit, terrain) {}

    void execute_attack() override;

    void apply_damage(decltype(src::unit::UnitParams::_base_damage_normal) incoming_normal);
    float calculate_normal_damage_over_distance();
    float calculate_normal_damage_through_cover_and_ducking(decltype(src::unit::UnitParams::_base_damage_normal) incoming_normal);
    float calculate_normal_damage_through_camo(decltype(src::unit::UnitParams::_base_damage_normal) incoming_normal);
};

};