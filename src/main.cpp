#include "std.hpp"
#include "gui/ApplicationFactory.hpp"

int main() {
    src::gui::ApplicationFactory::unit_plot_window().run();
    return 0;
}