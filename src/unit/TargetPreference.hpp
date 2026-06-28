#pragma once

namespace src::unit {

enum class TargetPreference : int {

  // Prefer to target units that do high damage of type ...
  Normal = 1,
  Explosive = 2,
  Artillery = 3

};

};