#pragma once
#include "../../src/std.hpp"
#include "../../src/unit/IUnit.hpp"
#include "../../src/unit/Unit.hpp"

namespace test::combat {

class UnitFactory {
public:
  static src::unit::UnitPtr standard(size_t team_id, size_t unit_id);
  static src::unit::UnitPtr normal_damage(size_t team_id, size_t unit_id,
                                          size_t base_damage_normal);
  static src::unit::UnitPtr alive_damage_and_morale(size_t team_id,
                                                    size_t unit_id,
                                                    size_t alive, size_t damage,
                                                    size_t base_morale);
  static src::unit::UnitPtr explosive_damage(size_t team_id, size_t unit_id,
                                          size_t base_damage_explosive);
  static src::unit::UnitPtr artillery_damage(size_t team_id, size_t unit_id,
                                          size_t base_damage_artillery);
  static src::unit::UnitPtr camo(size_t team_id, size_t unit_id, src::unit::CamoType camo);
  static src::unit::UnitPtr ducking(size_t team_id, size_t unit_id);
};

}; // namespace test::combat