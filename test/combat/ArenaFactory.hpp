#pragma once
#include "../../src/std.hpp"

#include "../../src/combat/Arena.hpp"
#include "ConfigurableTestUnit.hpp"
#include "TestUnit.hpp"

namespace test::combat {

class ArenaFactory {
public:
  static src::combat::ArenaPtr minimum_standard_arena();
  static src::combat::ArenaPtr standard_arena_1v3();
};

}; // namespace test::combat