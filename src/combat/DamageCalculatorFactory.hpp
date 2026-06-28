#pragma once
#include "IDamageCalculator.hpp"

#include "NormalDamageCalculator.hpp"

namespace src::combat {

class DamageCalculatorFactory {

public:
    static DamageCalculatorPtr normal_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain);

};

};