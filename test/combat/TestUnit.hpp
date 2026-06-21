#pragma once
#include "../../src/unit/IUnit.hpp"
#include "../../src/unit/UnitParams.hpp"

namespace test::combat {

class TestUnit : public src::unit::IUnit {
public:
  TestUnit(int team_id, size_t unit_id);
  ~TestUnit() override {}

  size_t unit_id() override;
  int team_id() override;

  int manpower() override;
  int alive() override;
  int wounded() override;

  int morale() override;
  int total_morale() override;
  virtual void apply_morale_damage(int incoming_damage) override;

  int damage_normal(float distance) override;
  void apply_normal(int incoming_normal) override;

  src::unit::TargetPreference preference() override;
  float preference_stiffness() override;

protected:
  src::unit::UnitParams params;
};

}; // namespace test::combat