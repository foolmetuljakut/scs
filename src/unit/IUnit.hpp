#pragma once
#include "../std.hpp"
#include "UnitParams.hpp"
#include "TargetPreference.hpp"
#include "CamoType.hpp"

namespace src::unit {

class IUnit {
public:
  virtual ~IUnit() {}

  virtual decltype(UnitParams::_unit_id) unit_id() = 0;
  virtual decltype(UnitParams::_team_id) team_id() = 0;

  virtual decltype(UnitParams::_troops_total) manpower() = 0;
  virtual decltype(UnitParams::_troops_alive) alive() = 0;
  virtual decltype(UnitParams::_troops_wounded) wounded() = 0;

  virtual decltype(UnitParams::_total_morale) morale() = 0;
  virtual decltype(UnitParams::_morale) total_morale() = 0;
  virtual void apply_morale_damage(decltype(UnitParams::_morale) incoming_damage, decltype(UnitParams::_morale) suppressed_damage) = 0;

  virtual decltype(UnitParams::_effective_range) effective_range() = 0;
  virtual decltype(UnitParams::_base_damage_normal) damage_normal() = 0;
  virtual decltype(UnitParams::_base_damage_explosives) damage_explosives() = 0;
  virtual decltype(UnitParams::_base_damage_artillery) damage_artillery() = 0;
  // later: explosives/splash/artillery, armor piercing / tank, ...
  virtual void apply_damage(float incoming) = 0;

  virtual decltype(UnitParams::_target_preference) preference() = 0;
  virtual decltype(UnitParams::_camo) camo() = 0;
  virtual decltype(UnitParams::_ducked) ducked() = 0;
  virtual decltype(UnitParams::_dug_in) dug_in() = 0;
};

typedef std::shared_ptr<IUnit> UnitPtr;

}; // namespace src::unit