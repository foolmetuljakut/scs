#pragma once
#include "../std.hpp"

#include "../unit/IUnit.hpp"

#include "../generic/MaxChoice.hpp"

namespace src::combat {

// TODO
//  - extract unit preference sorting responsibility
//    - leave for later
//  - extract choice responsibility
//    - make it simple: std::max_element with lambda [&units](auto& a, auto&b){
//    return a < b; }
//  - build new team-based unit collection responsibility
//    - using team-split lists of units / temporary calculation tables
//    - (vector of alives, vector of normal dmgs, ... so vectoring by stat
//    instead of unit-specific encapsulation)

class Arena {
public:
  void update_tick();
  size_t choose_opponent(size_t unit_index);

  void add_unit(const src::unit::UnitPtr &ptr);
  void remove_unit(const src::unit::UnitPtr &ptr);
  void clear();
  bool unit_involved(const src::unit::UnitPtr &ptr);
  bool unit_incapacitated(const src::unit::UnitPtr &ptr);
  void set_hostility(size_t team_a, size_t team_b);
  void remove_hostility(size_t team_a, size_t team_b);
  size_t size();
  src::unit::UnitPtr get_involved_unit(size_t index);

private:
  std::vector<src::unit::UnitPtr> units_involved;
  std::vector<std::pair<size_t, size_t>> hostilities; // match hostile team ids

  std::mt19937 rng{std::random_device{}()};

  std::vector<size_t> create_index_list(size_t n);
  void shuffle_index_list(std::vector<size_t> &index_list);
  bool are_hostile(size_t unit_index_a, size_t unit_index_b);
  std::vector<size_t> hostile_units_index_list(size_t acting_unit_index);
};

typedef std::shared_ptr<Arena> ArenaPtr;

}; // namespace src::combat