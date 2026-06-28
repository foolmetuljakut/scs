#include "Unit.hpp"

namespace src::unit {

Unit::Unit(decltype(UnitParams::_team_id) team_id, decltype(UnitParams::_unit_id) unit_id)
    : params {
        team_id, unit_id,
        1000, 1000, 0,
        100, 100,
        1,
        100,
        CamoType::Normal,
        TargetPreference::Normal
    } {}

Unit::Unit(decltype(UnitParams::_unit_id) unit_id, const UnitParams& other)
    : params {
        other._team_id, unit_id, 
        other._troops_total, other._troops_alive, other._troops_wounded, 
        other._total_morale, other._morale, 
        other._base_damage_normal,
        other._effective_range,
        other._camo,
        other._target_preference
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

decltype(UnitParams::_effective_range) Unit::effective_range() {
    return params._effective_range;
}

decltype(UnitParams::_base_damage_normal) Unit::damage_normal() {
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
    return params._target_preference;
}

CamoType Unit::camo() {
    return params._camo;
}

bool Unit::ducked() {
    return params._ducked;
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

Unit &Unit::range(decltype(UnitParams::_effective_range) set) {
    params._effective_range = set;
    return *this;
}

Unit &Unit::set_camo(decltype(UnitParams::_camo) set) {
    params._camo = set;
    return *this;
}

Unit &Unit::duck(decltype(UnitParams::_ducked) set) {
    params._ducked = set;
    return *this;
}

};