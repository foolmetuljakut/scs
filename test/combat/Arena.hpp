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

  arena->update_tick(); // one unit destroys the other -> removed from combat.
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

  auto destroyed_representative = arena->get_involved_unit(0);
  arena->update_tick(); // unit 0 vs unit 1-3 -> the single unit will definitely
                        // be incapacitated after an update

  REQUIRE(!arena->unit_involved(destroyed_representative));
}

TEST_CASE("Test Arena - victory by demoralization", "[require]") {
  auto arena = ArenaFactory::demoralizing_1v1();

  // we know _one_ unit will lose, just not which one
  auto unit_a = arena->get_involved_unit(
      0); // can do damage, but won't receive any -> will survive capable
  auto unit_b =
      arena->get_involved_unit(1); // can't do damage, but will receive enough
                                   // to break morale -> will be incapacitated

  arena->update_tick(); // one unit destroys the other -> removed from combat.
  REQUIRE(arena->size() == 1);

  bool one_unit_lost{arena->unit_incapacitated(unit_a) !=
                     arena->unit_incapacitated(unit_b)};
  REQUIRE(one_unit_lost);
  REQUIRE(unit_a->alive() > 0);
  REQUIRE(unit_b->alive() > 0);
}

// TODO write tests for edge cases:
//  2x2 grid of units completely covered / uncovered and 
//                    incoming damage insufficient / sufficient to hit all uncovered

TEST_CASE("Test Arena - cover - insufficient to hit uncovered (1/4)", "[require]") {
  // low damage scenario:
  // units are 1000 strong, cover for 1100 available 
  // => any attack (1000alive*1dmg) is not sufficient to overcome cover
  // => insufficient to hit (any) uncovered
  auto arena = ArenaFactory::partial_cover_arena(1100);

  auto unit_a = arena->get_involved_unit(0), unit_b = arena->get_involved_unit(1);
  float damage = unit_a->damage_normal(0.f);
  arena->apply_damage(unit_b, damage);

  REQUIRE(unit_b->alive() == 756);
}

TEST_CASE("Test Arena - cover - sufficient to hit uncovered (2/4)", "[require]") {
  // low mid damage scenario:
  // units are 1000 strong, cover for 900 available 
  // => any attack (1000alive*1dmg) is sufficient to overcome cover
  // => sufficient to hit (any) uncovered
  auto arena = ArenaFactory::partial_cover_arena(900);

  auto unit_a = arena->get_involved_unit(0), unit_b = arena->get_involved_unit(1);
  float damage = unit_a->damage_normal(0.f);
  arena->apply_damage(unit_b, damage);

  REQUIRE(unit_b->alive() == 681);
}

TEST_CASE("Test Arena - cover - insufficient to hit all covered (3/4)", "[require]") {
  // high mid damage scenario:
  // units are 1000 strong and do increased damage, full cover available
  // => any attack (1000alive*4dmg) is almost sufficient to overcome cover
  // => insufficient to hit (all) covered
  auto arena = ArenaFactory::partial_cover_arena(1000);

  auto unit_a = arena->get_involved_unit(0), unit_b = arena->get_involved_unit(1);
  std::dynamic_pointer_cast<src::unit::Unit>(unit_a)->base_damage(4); // weird upcast to set base damage: IUnit -> Unit
  float damage = unit_a->damage_normal(0.f);
  arena->apply_damage(unit_b, damage);

  REQUIRE(unit_b->alive() == 24);
}

TEST_CASE("Test Arena - cover - sufficient to hit all covered (4/4)", "[require]") {
  // high damage scenario:
  // units are 1000 strong and do increased damage, no full cover available
  // => any attack (1000alive*4dmg) is almost sufficient to overcome cover
  // => insufficient to hit (all) covered
  auto arena = ArenaFactory::partial_cover_arena(900);

  auto unit_a = arena->get_involved_unit(0), unit_b = arena->get_involved_unit(1);
  std::dynamic_pointer_cast<src::unit::Unit>(unit_a)->base_damage(4); // weird upcast to set base damage: IUnit -> Unit
  float damage = unit_a->damage_normal(0.f);
  arena->apply_damage(unit_b, damage);

  REQUIRE(unit_b->alive() == 0);
}

}; // namespace test::combat