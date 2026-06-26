#include "Unit.hpp"

namespace src::unit {

Unit::Unit(decltype(UnitParams::_team_id) team_id, decltype(UnitParams::_unit_id) unit_id)
    : params {
        team_id, unit_id,
        1000, 1000, 0,
        100, 100,
        1
    } {}

Unit::Unit(decltype(UnitParams::_unit_id) unit_id, const UnitParams& other)
    : params {
        other._team_id, unit_id, 
        other._troops_total, other._troops_alive, other._troops_wounded, 
        other._total_morale, other._morale, 
        other._base_damage_normal
    } {}

Unit::~Unit() {

}

decltype(UnitParams::_unit_id) Unit::unit_id() {
    return params._unit_id;
}

decltype(UnitParams::_team_id) Unit::team_id() {
    return params._team_id;
}

decltype(UnitParams::_troops_total) Unit::manpower() {
    return params._troops_total;
}

decltype(UnitParams::_troops_alive) Unit::alive() {
    return params._troops_alive;
}

decltype(UnitParams::_troops_wounded) Unit::wounded() {
    return params._troops_wounded;
}

decltype(UnitParams::_total_morale) Unit::morale() {
    return params._morale;
}

decltype(UnitParams::_morale) Unit::total_morale() {
    return params._total_morale;
}

void Unit::apply_morale_damage(decltype(UnitParams::_total_morale) incoming_damage) {
    incoming_damage = std::min(incoming_damage, params._morale);
    params._morale -= incoming_damage;
}

decltype(UnitParams::_base_damage_normal) Unit::damage_normal(float distance) {
    return params._base_damage_normal * alive();
}

void Unit::apply_normal(decltype(UnitParams::_base_damage_normal) incoming_normal) {
    incoming_normal = static_cast<decltype(UnitParams::_troops_alive)>(
        std::min(incoming_normal, static_cast<float>(params._troops_alive))
    );

    params._troops_alive -= incoming_normal;
    params._troops_wounded += incoming_normal;
}

TargetPreference Unit::preference() {
    return src::unit::TargetPreference::Normal;
}

float Unit::preference_stiffness() {
    return 0.1f; 
}

Unit &Unit::manpower(decltype(UnitParams::_troops_total) set) {
    params._troops_total = set;
    return *this;
}

Unit &Unit::alive(decltype(UnitParams::_troops_alive) set) {
    params._troops_alive = set;
    return *this;
}

Unit &Unit::wounded(decltype(UnitParams::_troops_wounded) set) {
    params._troops_wounded = set;
    return *this;
}

Unit &Unit::base_damage(decltype(UnitParams::_base_damage_normal) set) {
    params._base_damage_normal = set;
    return *this;
}

Unit &Unit::base_morale(decltype(UnitParams::_total_morale) set) {
    params._total_morale = set;
    params._morale = set;
    return *this;
}

};