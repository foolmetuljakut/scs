#pragma once
#include "../../src/unit/IUnit.hpp"

namespace test::combat {

class TestUnit : public src::unit::IUnit {
public:
  TestUnit(size_t team_id, size_t unit_id);
  ~TestUnit() override {}

  size_t unit_id() override;
  size_t team_id() override;

  void reset() override;

  size_t manpower() override;
  size_t alive() override;
  size_t wounded() override;

  size_t morale() override;
  size_t total_morale() override;
  virtual void apply_morale_damage(size_t incoming_damage) override;

  size_t damage_normal(float distance) override;
  void apply_normal(size_t incoming_normal) override;

  src::unit::TargetPreference preference() override;
  float preference_stiffness() override;

protected:
  size_t _team_id, _unit_id, troops_total, troops_alive, troops_wounded,
      _total_morale, _morale, base_damage_normal;
};

}; // namespace test::combat