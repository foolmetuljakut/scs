#include "UnitFactory.hpp"

namespace test::combat {

src::unit::UnitPtr UnitFactory::standard(size_t team_id, size_t unit_id) {
  return std::make_shared<src::unit::Unit>(team_id, unit_id);
}

src::unit::UnitPtr UnitFactory::normal_damage(size_t team_id, size_t unit_id,
                                              size_t base_damage_normal) {
  return std::make_shared<src::unit::Unit>(
      src::unit::Unit(team_id, unit_id)
          .base_damage(base_damage_normal));
}

src::unit::UnitPtr UnitFactory::alive_damage_and_morale(size_t team_id,
                                                        size_t unit_id,
                                                        size_t alive,
                                                        size_t damage,
                                                        size_t base_morale) {
  return std::make_shared<src::unit::Unit>(
      src::unit::Unit(team_id, unit_id)
          .alive(alive)
          .base_damage(damage)
          .base_morale(base_morale));
}

src::unit::UnitPtr UnitFactory::explosive_damage(size_t team_id, size_t unit_id,
                                              size_t base_damage_explosive) {
  return std::make_shared<src::unit::Unit>(
      src::unit::Unit(team_id, unit_id)
          .base_explosive_damage(base_damage_explosive));
}

src::unit::UnitPtr UnitFactory::artillery_damage(size_t team_id, size_t unit_id,
                                              size_t base_damage_artillery) {
  return std::make_shared<src::unit::Unit>(
      src::unit::Unit(team_id, unit_id)
          .base_artillery_damage(base_damage_artillery));
}

src::unit::UnitPtr UnitFactory::camo(size_t team_id, size_t unit_id, src::unit::CamoType camo) {
  return std::make_shared<src::unit::Unit>(
      src::unit::Unit(team_id, unit_id).set_camo(camo));
}

src::unit::UnitPtr UnitFactory::ducking(size_t team_id, size_t unit_id) {
  return std::make_shared<src::unit::Unit>(
      src::unit::Unit(team_id, unit_id).duck(true));
}

}; // namespace test::combat