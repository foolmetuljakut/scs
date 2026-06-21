#include "ApplicationFactory.hpp"

namespace src::gui {

GlfwApplication ApplicationFactory::unit_plot_window() {
    src::gui::GlfwApplication app("Unit Plot");
    app.set_drawable(std::make_shared<src::gui::content::UnitGraphPlot>());
    return app;
}

};