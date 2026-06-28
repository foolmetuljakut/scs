#include "Unit.hpp"

namespace src::unit {

Unit::Unit(decltype(UnitParams::_team_id) team_id, decltype(UnitParams::_unit_id) unit_id)
    : params {
        team_id, unit_id,
        1000, 1000, 0,
        100, 100,
        1, 0, 0,
        100,
        CamoType::Normal,
        TargetPreference::Normal
    } {}

Unit::Unit(decltype(UnitParams::_unit_id) unit_id, const UnitParams& other)
    : params {
        other._team_id, unit_id, 
        other._troops_total, other._troops_alive, other._troops_wounded, 
        other._total_morale, other._morale, 
        other._base_damage_normal, other._base_damage_explosives, other._base_damage_artillery,
        other._effective_range,
        other._camo,
        other._target_preference,
        other._ducked,
        other._dug_in
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

void Unit::apply_morale_damage(decltype(UnitParams::_morale) incoming_damage, decltype(UnitParams::_morale) suppressed_damage) {
    int morale_loss_by_kills = static_cast<int>(std::pow(incoming_damage / 5.f, 2.f)); // TODO: 5 / 2 are unconfirmed factors!
    int morale_loss_by_suppression = static_cast<int>(std::pow(suppressed_damage / 1000.f, 2.f)); // TODO: 1000 / 2 are unconfirmed factors!
    int morale_damage = std::min(morale_loss_by_kills, params._morale) +
        std::min(morale_loss_by_suppression, params._morale);
    params._morale -= morale_damage;
}

decltype(UnitParams::_effective_range) Unit::effective_range() {
    return params._effective_range;
}

decltype(UnitParams::_base_damage_normal) Unit::damage_normal() {
    return params._base_damage_normal * alive();
}

decltype(UnitParams::_base_damage_explosives) Unit::damage_explosives() {
    return params._base_damage_explosives * alive();
}

decltype(UnitParams::_base_damage_artillery) Unit::damage_artillery() {
    return params._base_damage_artillery * alive();
}

void Unit::apply_damage(float incoming) {
    incoming = static_cast<decltype(UnitParams::_troops_alive)>(
        std::min(incoming, static_cast<float>(params._troops_alive))
    );

    params._troops_alive -= incoming;
    params._troops_wounded += incoming;
}

decltype(UnitParams::_target_preference) Unit::preference() {
    return params._target_preference;
}

decltype(UnitParams::_camo) Unit::camo() {
    return params._camo;
}

decltype(UnitParams::_ducked) Unit::ducked() {
    return params._ducked;
}

decltype(UnitParams::_dug_in) Unit::dug_in() {
    return params._dug_in;
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

Unit &Unit::base_explosive_damage(decltype(UnitParams::_base_damage_explosives) set) {
    params._base_damage_explosives = set;
    return *this;
}

Unit &Unit::base_artillery_damage(decltype(UnitParams::_base_damage_artillery) set) {
    params._base_damage_artillery = set;
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

Unit &Unit::set_dug_in(decltype(UnitParams::_dug_in) set) {
    params._dug_in = set;
    return *this;
}

};