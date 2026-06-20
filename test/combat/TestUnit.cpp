#include "TestUnit.hpp"

namespace test::combat {

TestUnit::TestUnit(size_t team_id, size_t unit_id)
    : _team_id{team_id}, _unit_id{unit_id}, troops_total{100},
      troops_alive{100}, troops_wounded{0}, _total_morale{100}, _morale{100},
      base_damage_normal{1} {}

size_t TestUnit::unit_id() { return _unit_id; }

size_t TestUnit::team_id() { return _team_id; }

void TestUnit::reset() {
  troops_wounded = 0;
  troops_alive = troops_total;
}

size_t TestUnit::manpower() { return troops_total; }

size_t TestUnit::alive() { return troops_alive; }

size_t TestUnit::wounded() { return troops_wounded; }

size_t TestUnit::morale() { return _morale; }

size_t TestUnit::total_morale() { return _total_morale; }

void TestUnit::apply_morale_damage(size_t incoming_damage) {
  incoming_damage = std::min(incoming_damage, _morale);
  _morale -= incoming_damage;
}

size_t TestUnit::damage_normal(float distance) {
  return base_damage_normal * alive();
}

void TestUnit::apply_normal(size_t incoming_normal) {
  incoming_normal = std::min(incoming_normal, troops_alive);

  troops_alive -= incoming_normal;
  troops_wounded += incoming_normal;
}

src::unit::TargetPreference TestUnit::preference() {
  return src::unit::TargetPreference::Normal;
}

float TestUnit::preference_stiffness() { return 0.1f; }

}; // namespace test::combat