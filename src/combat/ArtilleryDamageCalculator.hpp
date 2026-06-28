#pragma once
#include "IDamageCalculator.hpp"

namespace src::combat {

class ArtilleryDamageCalculator : public IDamageCalculator {

public:
    ArtilleryDamageCalculator(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain)
        : IDamageCalculator(acting_unit, target_unit, terrain) {}

    void execute_attack() override;

    void apply_damage(decltype(src::unit::UnitParams::_base_damage_normal) incoming);
    float calculate_damage();
    float calculate_damage_through_cover(decltype(src::unit::UnitParams::_base_damage_normal) incoming);
};

};