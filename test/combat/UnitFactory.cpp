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

}; // namespace test::combat