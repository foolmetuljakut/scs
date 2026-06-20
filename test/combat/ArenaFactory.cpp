#include "ArenaFactory.hpp"

namespace test::combat {

src::combat::ArenaPtr ArenaFactory::minimum_standard_arena() {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1); // team 0 and team 1 are hostile
  arena->add_unit(std::make_shared<TestUnit>(0, 0)); // team 0, unit 0
  arena->add_unit(std::make_shared<TestUnit>(1, 1)); // team 1, unit 1
  return arena;
}

src::combat::ArenaPtr ArenaFactory::standard_arena_1v3() {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1); // team 0 and team 1 are hostile
  arena->add_unit(std::make_shared<TestUnit>(1, 0)); // team 1, unit 0
  arena->add_unit(std::make_shared<ConfigurableTestUnit>(
      ConfigurableTestUnit(0, 1).set_base_damage(3))); // team 0, unit 1
  arena->add_unit(std::make_shared<ConfigurableTestUnit>(
      ConfigurableTestUnit(0, 2).set_base_damage(2))); // team 0, unit 2
  arena->add_unit(std::make_shared<ConfigurableTestUnit>(
      ConfigurableTestUnit(0, 3).set_base_damage(1))); // team 0, unit 3
  return arena;
}

}; // namespace test::combat