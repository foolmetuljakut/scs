#pragma once
#include <catch2/catch_test_macros.hpp>

#include "ArenaFactory.hpp"

namespace test::combat {

TEST_CASE("Test Arena - hostile unit choice", "[require]") {
  auto arena = ArenaFactory::minimum_standard_arena();

  auto dummy_parameters = std::make_shared<TestUnit>(0, 0);

  REQUIRE(arena->choose_opponent(0, dummy_parameters) == 1);
  REQUIRE(arena->choose_opponent(1, dummy_parameters) == 0);
}

TEST_CASE("Test Arena - failing hostile unit choice after desctruction",
          "[require]") {
  auto arena = ArenaFactory::minimum_standard_arena();

  auto dummy_parameters = std::make_shared<TestUnit>(0, 0);
  arena->update_tick(); // unit 0 destroys unit 1 -> removed from combat. TestUnit ignores Distance

  REQUIRE_THROWS(arena->choose_opponent(0, dummy_parameters));
}

// TODO test with multiple ranked units of damage, use infinite stiffness and check if first unit is chosen over last

}; // namespace test::combat