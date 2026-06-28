#pragma once
#include "IDamageCalculator.hpp"

#include "NormalDamageCalculator.hpp"
#include "ExplosiveDamageCalculator.hpp"
#include "ArtilleryDamageCalculator.hpp"

namespace src::combat {

class DamageCalculatorFactory {

public:
    static DamageCalculatorPtr normal_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain);
    static DamageCalculatorPtr explosive_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain);
    static DamageCalculatorPtr artillery_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain);

};

};