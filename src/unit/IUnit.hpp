#pragma once
#include "../std.hpp"
#include "TargetPreference.hpp"

namespace src::unit {

class IUnit {
public:
  virtual ~IUnit() {}

  virtual size_t unit_id() = 0;
  virtual size_t team_id() = 0;

  virtual void reset() = 0;

  virtual size_t manpower() = 0;
  virtual size_t alive() = 0;
  virtual size_t wounded() = 0;

  virtual size_t morale() = 0;
  virtual size_t total_morale() = 0;
  virtual void apply_morale_damage(size_t incoming_damage) = 0;

  virtual size_t damage_normal(float distance) = 0;
  // later: explosives/splash/artillery, armor piercing / tank, ...
  virtual void apply_normal(size_t incoming_normal) = 0;

  virtual TargetPreference preference() = 0;
  virtual float preference_stiffness() = 0;
};

typedef std::shared_ptr<IUnit> UnitPtr;

}; // namespace src::unit