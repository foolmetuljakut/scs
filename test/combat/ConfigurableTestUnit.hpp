#pragma once
#include "TestUnit.hpp"

namespace test::combat {

class ConfigurableTestUnit : public test::combat::TestUnit {
public:
  ConfigurableTestUnit(size_t team_id, size_t unit_id)
      : TestUnit(team_id, unit_id) {}
  ~ConfigurableTestUnit() override {}

  ConfigurableTestUnit &set_manpower(size_t set) {
    troops_total = set;
    return *this;
  }
  ConfigurableTestUnit &set_alive(size_t set) {
    troops_alive = set;
    return *this;
  }
  ConfigurableTestUnit &set_wounded(size_t set) {
    troops_wounded = set;
    return *this;
  }
  ConfigurableTestUnit &set_base_damage(size_t set) {
    base_damage_normal = set;
    return *this;
  }
  ConfigurableTestUnit &set_base_morale(size_t set) {
    _total_morale = set;
    return *this;
  }
};

}; // namespace test::combat