#include "DamageCalculatorFactory.hpp"

namespace src::combat {

DamageCalculatorPtr DamageCalculatorFactory::normal_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain) {
    return std::make_shared<NormalDamageCalculator>(acting_unit, target_unit, terrain);
}

DamageCalculatorPtr DamageCalculatorFactory::explosive_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain) {
    return std::make_shared<ExplosiveDamageCalculator>(acting_unit, target_unit, terrain);
}

DamageCalculatorPtr DamageCalculatorFactory::artillery_damage(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain) {
    return std::make_shared<ArtilleryDamageCalculator>(acting_unit, target_unit, terrain);
}

};