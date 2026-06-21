#include "TestUnit.hpp"

namespace test::combat {

TestUnit::TestUnit(int team_id, size_t unit_id)
    : params {
      team_id, unit_id,
      100, 100, 0,
      100, 100,
      1
    } {}

size_t TestUnit::unit_id() { return params._unit_id; }

int TestUnit::team_id() { return params._team_id; }

int TestUnit::manpower() { return params._troops_total; }

int TestUnit::alive() { return params._troops_alive; }

int TestUnit::wounded() { return params._troops_wounded; }

int TestUnit::morale() { return params._morale; }

int TestUnit::total_morale() { return params._total_morale; }

void TestUnit::apply_morale_damage(int incoming_damage) {
  incoming_damage = std::min(incoming_damage, params._morale);
  params._morale -= incoming_damage;
}

int TestUnit::damage_normal(float distance) {
  return params._base_damage_normal * alive();
}

void TestUnit::apply_normal(int incoming_normal) {
  incoming_normal = std::min(incoming_normal, params._troops_alive);

  params._troops_alive -= incoming_normal;
  params._troops_wounded += incoming_normal;
}

src::unit::TargetPreference TestUnit::preference() {
  return src::unit::TargetPreference::Normal;
}

float TestUnit::preference_stiffness() { return 0.1f; }

}; // namespace test::combat