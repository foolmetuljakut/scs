#pragma once
#include "../../src/std.hpp"

#include "../../src/combat/Arena.hpp"
#include "UnitFactory.hpp"

namespace test::combat {

class ArenaFactory {
public:
  static src::combat::ArenaPtr minimum_standard_arena();
  static src::combat::ArenaPtr standard_arena_1v3();
  static src::combat::ArenaPtr demoralizing_1v1();
  static src::combat::ArenaPtr partial_cover_arena(int cover);
};

}; // namespace test::combat