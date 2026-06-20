#pragma once
#include <catch2/catch_test_macros.hpp>

#include "ArenaFactory.hpp"

namespace test::combat {

TEST_CASE("Test Arena - hostile unit choice", "[require]") {
  auto arena = ArenaFactory::minimum_standard_arena();

  REQUIRE(arena->choose_opponent(0) == 1);
  REQUIRE(arena->choose_opponent(1) == 0);
}

TEST_CASE("Test Arena - failing hostile unit choice after desctruction",
          "[require]") {
  auto arena = ArenaFactory::minimum_standard_arena();

  arena->update_tick(); // unit 0 destroys unit 1 -> removed from combat.
                        // TestUnit ignores Distance
  REQUIRE(arena->size() == 1);

  REQUIRE_THROWS(arena->choose_opponent(0));
}

TEST_CASE("Test Arena - test picking one of multiple units", "[require]") {
  auto arena = ArenaFactory::standard_arena_1v3();
  REQUIRE(arena->choose_opponent(0) ==
          1); // unit 0 chooses unit 1 for destruction, for having highest
              // damage value (preferred)
  REQUIRE(arena->choose_opponent(1) ==
          0); // unit 1 chooses unit 0 for being the only target
}

TEST_CASE("Test Arena - test targeting unit of highest value", "[require]") {
  auto arena = ArenaFactory::standard_arena_1v3();

  arena->update_tick(); // unit 0 attacks unit 1-3 -> removed from combat.
                        // TestUnit ignores Distance

  auto destroyed_representative = std::make_shared<TestUnit>(0, 1);
  REQUIRE(!arena->unit_involved(destroyed_representative));
}

// TODO test with multiple ranked units of damage, use infinite stiffness and
// check if first unit is chosen over last

}; // namespace test::combat