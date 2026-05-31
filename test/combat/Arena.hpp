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

  arena->update_tick(); // unit 0 destroys unit 1 -> removed from combat
  // TODO in Arena::update_tick() -> distance currently 0, so if > 0, test
  // expected to have to be fixed

  REQUIRE_THROWS(arena->choose_opponent(0));
}

}; // namespace test::combat