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

  decltype(UnitParams::_effective_range) effective_range() override;
  decltype(UnitParams::_base_damage_normal) damage_normal() override;
  decltype(UnitParams::_base_damage_explosives) damage_explosives() override;
  decltype(UnitParams::_base_damage_artillery) damage_artillery() override;
  void apply_damage(float incoming) override;

  decltype(UnitParams::_target_preference) preference() override;
  decltype(UnitParams::_camo) camo() override;
  decltype(UnitParams::_ducked) ducked() override;
  decltype(UnitParams::_dug_in) dug_in() override;

  Unit &manpower(decltype(UnitParams::_troops_total) set);
  Unit &alive(decltype(UnitParams::_troops_alive) set);
  Unit &wounded(decltype(UnitParams::_troops_wounded) set);
  Unit &base_damage(decltype(UnitParams::_base_damage_normal) set);
  Unit &base_explosive_damage(decltype(UnitParams::_base_damage_explosives) set);
  Unit &base_artillery_damage(decltype(UnitParams::_base_damage_artillery) set);
  Unit &base_morale(decltype(UnitParams::_total_morale) set);
  Unit &range(decltype(UnitParams::_effective_range) set);
  Unit &set_camo(decltype(UnitParams::_camo) set);
  Unit &duck(decltype(UnitParams::_ducked) set);
  Unit &set_dug_in(decltype(UnitParams::_dug_in) set);

private:
  UnitParams params;
};

};