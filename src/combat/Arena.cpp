#include "Arena.hpp"

namespace src::combat {

void Arena::update_tick() {

  auto unit_indices = create_index_list(units_involved.size());
  shuffle_index_list(unit_indices);

  for (size_t acting_unit_index : unit_indices) {
    auto acting_unit = units_involved[acting_unit_index];

    size_t hostile_unit_index;
    try {
      hostile_unit_index = choose_opponent(acting_unit_index);
    } catch (const std::runtime_error &) {
      return; // in case there are no opponents -> exception -> exit update
              // because only friendlies are present
    }

    src::unit::UnitPtr hostile_unit = units_involved[hostile_unit_index];

    if (unit_incapacitated(acting_unit)) {
      continue;
    }

    // TODO find distance
    float distance = 0;
    float damage_normal = acting_unit->damage_normal(distance);

    if (damage_normal > 0) {
      hostile_unit->apply_normal(damage_normal);
      hostile_unit->apply_morale_damage(damage_normal);
    }
  }

  std::erase_if(units_involved, [this](src::unit::UnitPtr &unit) {
    return unit_incapacitated(unit);
  });
}

size_t Arena::choose_opponent(size_t unit_index) {

  std::vector<size_t> indices = hostile_units_index_list(unit_index);
  if (indices.size() == 0) {
    throw std::runtime_error("no hostile combatants present");
  }
  if (indices.size() == 1) {
    return indices[0];
  }

  src::unit::TargetPreference pref = units_involved[unit_index]->preference();
  std::function<bool(const size_t &, const size_t &)> comp;

  switch (pref) {
  case src::unit::TargetPreference::Normal:
  default:
    // TODO replace close range approximation (0.0f)
    comp = [&, pref](const size_t &a, const size_t &b) {
      return units_involved[a]->damage_normal(0.0f) <
             units_involved[b]->damage_normal(0.0f);
    };
  }

  return src::generic::max_choice(indices, comp);
}

void Arena::add_unit(const src::unit::UnitPtr &ptr) {
  auto unit_it = std::find(units_involved.begin(), units_involved.end(), ptr);
  if (unit_it == units_involved.end()) {
    units_involved.push_back(ptr);
  }
}

void Arena::remove_unit(const src::unit::UnitPtr &ptr) {
  auto unit_it = std::find(units_involved.begin(), units_involved.end(), ptr);
  if (unit_it == units_involved.end()) {
    return;
  }
  units_involved.erase(unit_it);
}

bool Arena::unit_involved(const src::unit::UnitPtr &ptr) {
  return std::find(units_involved.begin(), units_involved.end(), ptr) !=
         units_involved.end();
}

bool Arena::unit_incapacitated(const src::unit::UnitPtr &unit) {
  return unit->alive() == 0 || unit->morale() == 0;
}

void Arena::set_hostility(size_t team_a, size_t team_b) {
  auto match = std::find(hostilities.begin(), hostilities.end(),
                         std::pair{team_a, team_b});
  if (match == hostilities.end()) {
    hostilities.push_back({team_a, team_b});
  }
}

void Arena::remove_hostility(size_t team_a, size_t team_b) {
  auto match = std::find(hostilities.begin(), hostilities.end(),
                         std::pair{team_a, team_b});
  if (match != hostilities.end()) {
    hostilities.erase(match);
  }
}

size_t Arena::size() { return units_involved.size(); }

src::unit::UnitPtr Arena::get_involved_unit(size_t index) {
  return units_involved[index];
}

std::vector<size_t> Arena::create_index_list(size_t n) {
  std::vector<size_t> indices(n);
  for (size_t i = 0; i < n; i++) {
    indices[i] = i;
  }
  return indices;
}

void Arena::shuffle_index_list(std::vector<size_t> &index_list) {
  auto rng = std::default_random_engine{};
  std::shuffle(index_list.begin(), index_list.end(), rng);
}

bool Arena::are_hostile(size_t unit_index_a, size_t unit_index_b) {
  size_t team_a = units_involved[unit_index_a]->team_id();
  size_t team_b = units_involved[unit_index_b]->team_id();

  bool found_a_b_hostility{std::find(hostilities.begin(), hostilities.end(),
                                     std::pair{team_a, team_b}) !=
                           hostilities.end()};
  bool found_b_a_hostility{std::find(hostilities.begin(), hostilities.end(),
                                     std::pair{team_b, team_a}) !=
                           hostilities.end()};
  return found_a_b_hostility || found_b_a_hostility;
}

std::vector<size_t> Arena::hostile_units_index_list(size_t acting_unit_index) {
  size_t n = units_involved.size();
  std::vector<size_t> indices;
  indices.reserve(n);
  for (size_t other_unit_index = 0; other_unit_index < n; other_unit_index++) {
    if (are_hostile(acting_unit_index, other_unit_index)) {
      indices.push_back(other_unit_index);
    }
  }
  return indices;
}

}; // namespace src::combat