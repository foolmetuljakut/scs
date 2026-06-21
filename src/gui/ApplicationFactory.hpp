#pragma once
#include "../std.hpp"

#include "GlfwApplication.hpp"
#include "content/UnitGraphPlot.hpp"


namespace src::gui {

class ApplicationFactory {
public:
    static GlfwApplication unit_plot_window();
};

};