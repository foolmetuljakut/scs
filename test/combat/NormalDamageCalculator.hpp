#pragma once
#include <catch2/catch_test_macros.hpp>

#include "UnitFactory.hpp"
#include "../../src/combat/NormalDamageCalculator.hpp"

namespace test::combat {

using Normal = src::combat::NormalDamageCalculator;

TEST_CASE("Test Arena - damage over distance drop off", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::Normal}; // 0 cover, 0 max range, normal landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_a)->range(100);

  float damage_at_0 = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();

  terrain = src::combat::Terrain{0, 50, src::unit::CamoType::Normal}; // 0 cover, max range = 50% of effective range
  float damage_at_50 = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();

  terrain = src::combat::Terrain{0, 100, src::unit::CamoType::Normal}; // 0 cover, max range = effective range
  float damage_at_100 = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();

  terrain = src::combat::Terrain{0, 200, src::unit::CamoType::Normal}; // 0 cover, max range = twice effective range
  float damage_at_200 = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();

  // at perfect aim ...
  REQUIRE(damage_at_0 == damage_at_50); // zero distance and full coverage is equal
  REQUIRE(std::abs(damage_at_100 / damage_at_50 - 0.5f) < 1e-6 ); // at the effective range we have 50% hit chance
  REQUIRE(damage_at_100 == damage_at_200); // at a greater distance than the effective range the unit moves up to that distance
}

TEST_CASE("Test Arena - camo - no effect from no camo", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::Normal}; // 0 cover, 0 max range, normal landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->set_camo(src::unit::CamoType::Normal);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_camo = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_camo(theoretical_damage);

  REQUIRE(theoretical_damage == damage_including_camo);
}

TEST_CASE("Test Arena - camo - good effect from matching camo", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::GrassPlains}; // 0 cover, 0 max range, GrassPlains landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->set_camo(src::unit::CamoType::GrassPlains);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_camo = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_camo(theoretical_damage);

  REQUIRE(theoretical_damage >= 5 * damage_including_camo);
}

TEST_CASE("Test Arena - camo - no effect from non-matching camo", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::TundraPlains}; // 0 cover, 0 max range, Trundra landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->set_camo(src::unit::CamoType::GrassPlains);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_camo = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_camo(theoretical_damage);

  REQUIRE(theoretical_damage == damage_including_camo);
}

TEST_CASE("Test Arena - ducking - no effect from not ducking", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::Normal}; // 0 cover, 0 max range, normal landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->duck(false);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_ducking = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_cover_and_ducking(theoretical_damage);

  REQUIRE(theoretical_damage == damage_including_ducking);
}

TEST_CASE("Test Arena - ducking - good effect from ducking", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::GrassPlains}; // 0 cover, 0 max range, GrassPlains landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->duck(true);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_ducking = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_cover_and_ducking(theoretical_damage);

  REQUIRE(theoretical_damage >= 2.5 * damage_including_ducking);
}

TEST_CASE("Test Arena - ducking - no additional benefit from ducking if in cover", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{1000, 0, src::unit::CamoType::GrassPlains}; // 1000 cover, 0 max range, GrassPlains landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->duck(true);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_actually_from_cover = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_cover_and_ducking(theoretical_damage);

  REQUIRE(src::combat::Terrain::_ducking_factor * theoretical_damage > damage_actually_from_cover);
}

TEST_CASE("Test Arena - digging in - no effect from not being dug in", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::Normal}; // 0 cover, 0 max range, normal landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->set_dug_in(false);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_dug_in = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_cover_and_ducking(theoretical_damage);

  REQUIRE(theoretical_damage == damage_including_dug_in);
}

TEST_CASE("Test Arena - digging in - being dug in counts as covered", "[require]") {
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{0, 0, src::unit::CamoType::GrassPlains}; // 0 cover - but we will get full cover by digging in, 0 max range, GrassPlains landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_b)->set_dug_in(true);

  float theoretical_damage = Normal(unit_a, unit_b, terrain).calculate_normal_damage_over_distance();
  float damage_including_dug_in = Normal(unit_a, unit_b, terrain).calculate_normal_damage_through_cover_and_ducking(theoretical_damage);

  REQUIRE(src::combat::Terrain::_cover_factor * theoretical_damage == damage_including_dug_in);
}

// tests for edge cases:
//  2x2 grid of units completely covered / uncovered and 
//                    incoming damage insufficient / sufficient to hit all uncovered

TEST_CASE("Test Arena - cover - insufficient to hit uncovered (1/4)", "[require]") {
  // low damage scenario:
  // units are 1000 strong, cover for 1100 available
  // => any attack (1000alive*1dmg) is not sufficient to overcome cover
  // => insufficient to hit (any) uncovered
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{1100, 0, src::unit::CamoType::Normal}; // 1100 cover, 0 max range, normal landscape

  Normal(unit_a, unit_b, terrain).execute_attack();

  REQUIRE(unit_b->alive() == 756);
}

TEST_CASE("Test Arena - cover - sufficient to hit uncovered (2/4)", "[require]") {
  // low mid damage scenario:
  // units are 1000 strong, cover for 900 available 
  // => any attack (1000alive*1dmg) is sufficient to overcome cover
  // => sufficient to hit (any) uncovered
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{900, 0, src::unit::CamoType::Normal}; // 900 cover, 0 max range, normal landscape

  Normal(unit_a, unit_b, terrain).execute_attack();

  REQUIRE(unit_b->alive() == 681);
}

TEST_CASE("Test Arena - cover - insufficient to hit all covered (3/4)", "[require]") {
  // high mid damage scenario:
  // units are 1000 strong and do increased damage, full cover available
  // => any attack (1000alive*4dmg) is almost sufficient to overcome cover
  // => insufficient to hit (all) covered
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{1000, 0, src::unit::CamoType::Normal}; // 1000 cover, 0 max range, normal landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_a)->base_damage(4); // weird upcast to set base damage: IUnit -> Unit

  Normal(unit_a, unit_b, terrain).execute_attack();

  REQUIRE(unit_b->alive() == 24);
}

TEST_CASE("Test Arena - cover - sufficient to hit all covered (4/4)", "[require]") {
  // high damage scenario:
  // units are 1000 strong and do increased damage, no full cover available
  // => any attack (1000alive*4dmg) is almost sufficient to overcome cover
  // => insufficient to hit (all) covered
  auto unit_a = UnitFactory::standard(0, 0), unit_b = UnitFactory::standard(1, 1);
  src::combat::Terrain terrain{900, 0, src::unit::CamoType::Normal}; // 900 cover, 0 max range, normal landscape
  std::dynamic_pointer_cast<src::unit::Unit>(unit_a)->base_damage(4); // weird upcast to set base damage: IUnit -> Unit

  Normal(unit_a, unit_b, terrain).execute_attack();

  REQUIRE(unit_b->alive() == 0);
}

};