#pragma once
#include "../../std.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

#include "Config.hpp"
#include "../IDrawable.hpp"
#include "../../combat/Arena.hpp"
#include "../../unit/Unit.hpp"
#include "../../unit/UnitParams.hpp"

namespace src::gui::content {

class UnitGraphPlot : public src::gui::IDrawable {
public:
    UnitGraphPlot();
    ~UnitGraphPlot() override;

    void draw();

private:

    void configure_update();
    void configure_unit();
    void basic_unit_config();
    void detailed_unit_config();
    void configure_plot_window();
    void configure_plot_axes();
    void plot_units();

    void reset();
    void update_tick();
    void add_unit(decltype(src::unit::UnitParams::_team_id) team_id);

    Config config;

    src::combat::ArenaPtr _arena;
    std::vector<uint32_t> _time_values;
    std::vector<src::unit::UnitPtr> _units;
    std::vector<std::vector<uint32_t>> _alive_per_unit;

    // Gui parameters
    bool _create_unit_all_params;
    src::unit::UnitParams _create_unit_template;
};

};