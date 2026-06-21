#pragma once
#include "IUnit.hpp"
#include "UnitParams.hpp"

namespace src::unit {

class Unit: public IUnit {
public:
  Unit(decltype(UnitParams::_team_id) team_id, decltype(UnitParams::_unit_id) unit_id);
  Unit(decltype(UnitParams::_unit_id) unit_id, const UnitParams& other);
  ~Unit() override;

  decltype(UnitParams::_unit_id) unit_id() override;
  decltype(UnitParams::_team_id) team_id() override;

  decltype(UnitParams::_troops_total) manpower() override;
  decltype(UnitParams::_troops_alive) alive() override;
  decltype(UnitParams::_troops_wounded) wounded() override;

  decltype(UnitParams::_total_morale) total_morale() override;
  decltype(UnitParams::_morale) morale() override;
  virtual void apply_morale_damage(decltype(UnitParams::_total_morale) incoming_damage) override;

  decltype(UnitParams::_base_damage_normal) damage_normal(float distance) override;
  void apply_normal(decltype(UnitParams::_base_damage_normal) incoming_normal) override;

  src::unit::TargetPreference preference() override;
  float preference_stiffness() override;

  Unit &manpower(decltype(UnitParams::_troops_total) set);
  Unit &alive(decltype(UnitParams::_troops_alive) set);
  Unit &wounded(decltype(UnitParams::_troops_wounded) set);
  Unit &base_damage(decltype(UnitParams::_base_damage_normal) set);
  Unit &base_morale(decltype(UnitParams::_total_morale) set);

private:
  UnitParams params;
};

};