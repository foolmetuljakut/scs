#include "ArenaFactory.hpp"

namespace test::combat {

src::combat::ArenaPtr ArenaFactory::minimum_standard_arena() {
  auto arena = std::make_shared<src::combat::Arena>();
  arena->set_hostility(0, 1); // team 0 and team 1 are hostile
  arena->add_unit(std::make_shared<TestUnit>(0, 0)); // team 0, unit 0
  arena->add_unit(std::make_shared<TestUnit>(1, 1)); // team 1, unit 1
  return arena;
}

}; // namespace test::combat