#pragma once
#include <catch2/catch_test_macros.hpp>

#include "UnitFactory.hpp"
#include "../../src/combat/ArtilleryDamageCalculator.hpp"

namespace test::combat {

using Artillery = src::combat::ArtilleryDamageCalculator;

// TODO write tests nailing properties of large explosives like artillery

TEST_CASE("Test ArtilleryDamageCalculator - bypasses camo", "[require]") {
  auto unit_a = UnitFactory::artillery_damage(0, 0, 1), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::GrassPlains}; // 0 cover, 0 max range, GrassPlains landscape

  float theoretical_damage = Artillery(unit_a, unit_b, terrain).calculate_damage();
  float damage_including_cover = Artillery(unit_a, unit_b, terrain).calculate_damage_through_cover(theoretical_damage);

  REQUIRE(theoretical_damage == damage_including_cover);
}

TEST_CASE("Test ArtilleryDamageCalculator - avoided by cover", "[require]") {
  auto unit_a = UnitFactory::artillery_damage(0, 0, 1), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{1000, 0, src::unit::CamoType::GrassPlains}; // 1000 cover, 0 max range, GrassPlains landscape

  float theoretical_damage = Artillery(unit_a, unit_b, terrain).calculate_damage();
  float damage_including_cover = Artillery(unit_a, unit_b, terrain).calculate_damage_through_cover(theoretical_damage);

  REQUIRE(theoretical_damage > damage_including_cover);
}

};