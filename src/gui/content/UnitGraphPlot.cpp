#pragma once
#include "UnitGraphPlot.hpp"

namespace src::gui::content {

UnitGraphPlot::UnitGraphPlot()
    : _arena{std::make_shared<src::combat::Arena>()}
    , _create_unit_all_params{false}
    , _create_unit_template{0, 1, 1000, 1000, 0, 100, 100, 1} {
    config.load("./etc/params.cfg");
    _arena->set_hostility(0, 1);
    _time_values.push_back(0); // units add their troop numbers on start
    add_unit(0);
    add_unit(1);
}

UnitGraphPlot::~UnitGraphPlot() {

}

void UnitGraphPlot::draw() {
    configure_plot_window();
    configure_unit();
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
    const char* options[] = { "Team A", "Team B" };

    ImGui::Combo("Team A/B?", &_create_unit_template._team_id, options, IM_ARRAYSIZE(options));
    ImGui::InputInt("Troops total", &_create_unit_template._troops_total);
    ImGui::InputInt("Morale pts total", &_create_unit_template._total_morale);
    ImGui::Checkbox("Show details", &_create_unit_all_params);
}

void UnitGraphPlot::detailed_unit_config() {
    ImGui::InputInt("Troops alive", &_create_unit_template._troops_alive);
    ImGui::InputInt("Troops wounded", &_create_unit_template._troops_wounded);
    ImGui::InputInt("Morale pts", &_create_unit_template._morale);
    ImGui::InputInt("Base dmg / troop", &_create_unit_template._base_damage_normal);
}

void UnitGraphPlot::configure_plot_window() {
    ImGui::Begin("Development plot");
    ImGui::Text("Development of troops of unit still in action vs. time");

    configure_plot_axes();
    if (ImPlot::BeginPlot("Alive")) {
        plot_units();
        ImPlot::EndPlot();
    }

    ImGui::End();
}

void UnitGraphPlot::configure_plot_axes() {

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
    _arena->update_tick();
    _time_values.push_back(static_cast<uint32_t>(_time_values.size()));

    for(size_t i = 0; i < _units.size(); i++) {
        _alive_per_unit[i].push_back(static_cast<uint32_t>(_units[i]->alive()));
    }
}

};