#pragma once
#include "TestUnit.hpp"

namespace test::combat {

class ConfigurableTestUnit : public test::combat::TestUnit {
public:
  ConfigurableTestUnit(int team_id, size_t unit_id)
      : TestUnit(team_id, unit_id) {}
  ~ConfigurableTestUnit() override {}

  ConfigurableTestUnit &set_manpower(int set) {
    params._troops_total = set;
    return *this;
  }
  ConfigurableTestUnit &set_alive(int set) {
    params._troops_alive = set;
    return *this;
  }
  ConfigurableTestUnit &set_wounded(int set) {
    params._troops_wounded = set;
    return *this;
  }
  ConfigurableTestUnit &set_base_damage(int set) {
    params._base_damage_normal = set;
    return *this;
  }
  ConfigurableTestUnit &set_base_morale(int set) {
    params._total_morale = set;
    return *this;
  }
};

}; // namespace test::combat