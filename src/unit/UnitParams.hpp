#pragma once
#include "../std.hpp"
#include "TargetPreference.hpp"
#include "CamoType.hpp"

namespace src::unit {

// POD with parameters access-managed by Unit
struct UnitParams {
  int _team_id;
  size_t _unit_id;
  int _troops_total, _troops_alive, _troops_wounded;
  int _total_morale, _morale;
  float _base_damage_normal;
  int _effective_range;
  CamoType _camo;
  TargetPreference _target_preference;
  bool _ducked, _dug_in;
};

};