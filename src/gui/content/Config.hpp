#pragma once
#include "../../std.hpp"


namespace src::gui::content {

struct Config {
    void log();
    void load(const std::string& filename);
};

}; // namespace src::config