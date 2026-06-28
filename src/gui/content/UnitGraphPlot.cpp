#pragma once
#include "UnitGraphPlot.hpp"

namespace src::gui::content {

UnitGraphPlot::UnitGraphPlot()
    : _arena{std::make_shared<src::combat::Arena>()}
    , _create_unit_all_params{false}
    , _create_unit_template{0, 1, 1000, 1000, 0, 100, 100, 0.1f, 0.f, 0.f, 100, src::unit::CamoType::Normal, src::unit::TargetPreference::Normal, false, false}
    , _create_unit_camo_selector{0}
    , _create_terrain_template{1000, 100}
    , _create_terrain_camo_selector{0} {
    config.load("./etc/params.cfg");
    _arena->set_hostility(0, 1);
}

UnitGraphPlot::~UnitGraphPlot() {

}

void UnitGraphPlot::draw() {
    configure_plot_window();
    configure_unit();
    configure_terrain();
    configure_update();
}

void UnitGraphPlot::configure_update() {
    ImGui::Begin("Update Tick");

    ImVec2 button_dim(1267, 30);
    if(ImGui::Button("Update Tick", button_dim)) {
        update_tick();
    }

    ImGui::End();
}

void UnitGraphPlot::configure_unit() {
    ImGui::Begin("Configure Units");

    basic_unit_config();
    if(_create_unit_all_params) {
        detailed_unit_config();
    }

    ImVec2 button_dim(70, 30);
    if(ImGui::Button("Add Unit", button_dim)) {
        add_unit(_create_unit_template._team_id);
    }

    for(const auto& unit : _units) {
        std::string s = "Unit " + std::to_string(unit->unit_id()) + std::string(" (team ") + 
            std::string(unit->team_id() ? "B " : "A ") + std::to_string(unit->alive()) + 
            std::string(" alive)");
        ImGui::Text(s.c_str());
    }

    ImGui::End();
}

void UnitGraphPlot::basic_unit_config() {
    const char* team_options[] = { "Team A", "Team B" };

    ImGui::Combo("Team A/B?", &_create_unit_template._team_id, team_options, IM_ARRAYSIZE(team_options));
    ImGui::InputInt("Troops total", &_create_unit_template._troops_total);
    ImGui::InputInt("Morale pts total", &_create_unit_template._total_morale);
    ImGui::Checkbox("Show details", &_create_unit_all_params);
}

void UnitGraphPlot::detailed_unit_config() {
    ImGui::InputInt("Troops alive", &_create_unit_template._troops_alive);
    ImGui::InputInt("Troops wounded", &_create_unit_template._troops_wounded);
    ImGui::InputInt("Morale pts", &_create_unit_template._morale);
    ImGui::InputFloat("Base dmg / troop", &_create_unit_template._base_damage_normal, 1.f);
    ImGui::InputFloat("Grenade dmg / troop", &_create_unit_template._base_damage_explosives, 1.f);
    ImGui::InputFloat("Artillery dmg / troop", &_create_unit_template._base_damage_artillery, 1.f);
    ImGui::InputInt("Eff. Range", &_create_unit_template._effective_range, 1.f);
    ImGui::Checkbox("Duck and cover", &_create_unit_template._ducked);
    ImGui::Checkbox("Dig in", &_create_unit_template._dug_in);

    const char* camo_options[] = { 
        "Normal",
        "GrassPlains",
        "TundraPlains",
        "DesertPlains",
        "ArcticPlains",
        "Urbanous",
        "Mountainous",
        "DeciduousForest",
        "ConiferousForest",
        "DjungleForest" 
    };
    ImGui::Combo("Camo type", &_create_unit_camo_selector, camo_options, IM_ARRAYSIZE(camo_options));
    _create_unit_template._camo = src::unit::CamoType{_create_unit_camo_selector};
}

void UnitGraphPlot::configure_terrain() {
    ImGui::Begin("Configure Terrain");
    
    ImGui::InputInt("Coverable troops", &_create_terrain_template._cover_provision);
    ImGui::InputInt("Max range", &_create_terrain_template._max_distance);

    const char* camo_options[] = { 
        "Normal",
        "GrassPlains",
        "TundraPlains",
        "DesertPlains",
        "ArcticPlains",
        "Urbanous",
        "Mountainous",
        "DeciduousForest",
        "ConiferousForest",
        "DjungleForest" 
    };
    ImGui::Combo("Camo type", &_create_terrain_camo_selector, camo_options, IM_ARRAYSIZE(camo_options));
    _create_terrain_template._terrain_type = src::unit::CamoType{_create_terrain_camo_selector};

    ImGui::End();
}

void UnitGraphPlot::configure_plot_window() {
    ImGui::Begin("Development plot");
    ImGui::Text("Development of troops of unit still in action vs. time");

    configure_plot_axes();
    if (ImPlot::BeginPlot("Alive")) {
        plot_units();
        ImPlot::EndPlot();
    }

    for(size_t i = 0; i < _time_values.size(); i++) {
        std::string s = "Round " + std::to_string(i) + std::string(". alive: ");
        for(size_t j = 0; j < _alive_per_unit.size(); j++) {
            s += std::to_string(_alive_per_unit[j][i]) + std::string(", ");
        }
        ImGui::Text(s.c_str());
    }

    ImGui::End();
}

void UnitGraphPlot::configure_plot_axes() {

    if(_time_values.size() == 0) {
        return;
    }

    uint32_t t_min = *std::min_element(_time_values.begin(), _time_values.end()),
            t_max = *std::max_element(_time_values.begin(), _time_values.end());
    
    uint32_t a_min = 0, a_max = 1;
    if(_alive_per_unit.size() > 0) {
        a_max = *std::max_element(_alive_per_unit[0].begin(), _alive_per_unit[0].end());
    }
    double dt = t_max - t_min, da = a_max - a_min;
    double t_offset_l = 0.15 * dt, t_offset_r = 0.05 * dt, a_offset_u = 0.05 * da, a_offset_d = 0.15 * da;

    ImPlot::SetNextAxesLimits(t_min - t_offset_l, t_max + t_offset_r, a_min - a_offset_d, a_max + a_offset_u, ImGuiCond_Always);
}

void UnitGraphPlot::plot_units() {
    ImPlot::SetupAxes("Time", "Troops alive");
    int time_length = static_cast<int>(_time_values.size());
    for(size_t i = 0; i < _alive_per_unit.size(); i++) {
        const auto& alive_series = _alive_per_unit[i];
        std::string label = "Unit " + std::to_string(i);
        ImPlot::PlotLine(label.c_str(), _time_values.data(), alive_series.data(), time_length);
    }
}

void UnitGraphPlot::reset() {
    _arena->clear();
    _units.clear();
    _time_values.clear();
    _alive_per_unit.clear();
}

void UnitGraphPlot::add_unit(decltype(src::unit::UnitParams::_team_id) team_id) {
    _create_unit_template._team_id = team_id;
    // creates a copy of the pre configured unit except a unique unit-id (_units.size()), makes it shared and passes it into the _arena
    _units.push_back(std::make_shared<src::unit::Unit>(_units.size(), _create_unit_template));
    _arena->add_unit(_units.back());
    _alive_per_unit.push_back(std::vector<uint32_t>());
    _alive_per_unit.back().push_back(static_cast<uint32_t>(_units.back()->alive()));
}

void UnitGraphPlot::update_tick() {
    _arena->set_terrain(_create_terrain_template);
    _arena->update_tick();
    _time_values.push_back(static_cast<uint32_t>(_time_values.size()));

    for(size_t i = 0; i < _units.size(); i++) {
        _alive_per_unit[i].push_back(static_cast<uint32_t>(_units[i]->alive()));
    }
}

};