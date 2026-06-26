#include "ArenaFactory.hpp"

namespace test::combat {

src::combat::ArenaPtr ArenaFactory::minimum_standard_arena() {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1);                   // team 0 and team 1 are hostile
  arena->add_unit(UnitFactory::standard(0, 0)); // team 0, unit 0
  arena->add_unit(UnitFactory::standard(1, 1)); // team 1, unit 1
  return arena;
}

src::combat::ArenaPtr ArenaFactory::standard_arena_1v3() {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1);                   // team 0 and team 1 are hostile
  arena->add_unit(UnitFactory::standard(1, 0)); // team 1, unit 0
  arena->add_unit(UnitFactory::normal_damage(0, 1, 3)); // team 0, unit 1
  arena->add_unit(UnitFactory::normal_damage(0, 2, 2)); // team 0, unit 2
  arena->add_unit(UnitFactory::normal_damage(0, 4, 1)); // team 0, unit 3
  return arena;
}

src::combat::ArenaPtr ArenaFactory::demoralizing_1v1() {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1); // team 0 and team 1 are hostile
  arena->add_unit(UnitFactory::alive_damage_and_morale(
      0, 0, 100, 1, 100)); // team 0, unit 0 - can do damage
  arena->add_unit(UnitFactory::alive_damage_and_morale(
      1, 1, 1000, 0, 100)); // team 1, unit 1 - can't do damage
  return arena;
}

src::combat::ArenaPtr ArenaFactory::partial_cover_arena(int cover) {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1);                   // team 0 and team 1 are hostile
  arena->add_unit(UnitFactory::standard(0, 0)); // team 0, unit 0
  arena->add_unit(UnitFactory::standard(1, 1)); // team 1, unit 1
  arena->set_terrain(src::combat::Terrain{cover});
  return arena;
}

}; // namespace test::combat