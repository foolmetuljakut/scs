#include "Config.hpp"

namespace src::gui::content {

void Config::log() {
    spdlog::debug("Algorithm settings:");
}

void Config::load(const std::string& filename) {
    libconfig::Config config;

    try {
        config.readFile(filename.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        spdlog::error("I/O error while reading file: {}", filename);
    } catch (const libconfig::ParseException& pex) {
        spdlog::error("Parse error at {}:{} - {}", pex.getFile(), pex.getLine(), pex.getError());
    }

    spdlog::set_level(static_cast<spdlog::level::level_enum>((int)config.lookup("log_level")));
}

}; // namespace src::config