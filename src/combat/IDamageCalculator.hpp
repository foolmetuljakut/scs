#pragma once
#include "../std.hpp"

#include "../unit/IUnit.hpp"
#include "../unit/UnitParams.hpp"
#include "Terrain.hpp"

namespace src::combat {

class IDamageCalculator {
public:
    IDamageCalculator(const src::unit::UnitPtr& acting_unit, const src::unit::UnitPtr& target_unit, const Terrain& terrain)
        : acting_unit{acting_unit}, target_unit{target_unit}, terrain{terrain} {}
    
    virtual void execute_attack() = 0;

protected:
    src::unit::UnitPtr acting_unit, target_unit; 
    Terrain terrain;

};

typedef std::shared_ptr<IDamageCalculator> DamageCalculatorPtr;

}