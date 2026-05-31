#pragma once
#include "../../src/std.hpp"

#include "../../src/combat/Arena.hpp"
#include "TestUnit.hpp"

namespace test::combat {

class ArenaFactory {
public:
  static src::combat::ArenaPtr minimum_standard_arena();
};

}; // namespace test::combat