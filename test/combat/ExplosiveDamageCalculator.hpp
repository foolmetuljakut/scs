#pragma once
#include <catch2/catch_test_macros.hpp>

#include "UnitFactory.hpp"
#include "../../src/combat/ExplosiveDamageCalculator.hpp"

namespace test::combat {

using Explosive = src::combat::ExplosiveDamageCalculator;

// TODO write tests nailing properties of small explosives

TEST_CASE("Test ExplosiveDamageCalculator - bypasses cover", "[require]") {
  auto unit_a = UnitFactory::explosive_damage(0, 0, 1), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{1000, 0, src::unit::CamoType::Normal}; // 1000 cover, 0 max range, normal landscape

  float theoretical_damage = Explosive(unit_a, unit_b, terrain).calculate_damage_over_distance();
  float damage_including_cover = Explosive(unit_a, unit_b, terrain).calculate_damage_through_ducking(theoretical_damage);

  REQUIRE(theoretical_damage == damage_including_cover);
}

TEST_CASE("Test ExplosiveDamageCalculator - avoided by ducking", "[require]") {
  auto unit_a = UnitFactory::explosive_damage(0, 0, 1), unit_b = UnitFactory::ducking(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::Normal}; // 0 cover, 0 max range, normal landscape

  float theoretical_damage = Explosive(unit_a, unit_b, terrain).calculate_damage_over_distance();
  float damage_including_cover = Explosive(unit_a, unit_b, terrain).calculate_damage_through_ducking(theoretical_damage);

  REQUIRE(theoretical_damage > damage_including_cover);
}

};