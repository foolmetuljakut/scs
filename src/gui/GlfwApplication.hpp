#pragma once
#include "../std.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <implot.h>

#include <GLFW/glfw3.h>

#include "IDrawable.hpp"

namespace src::gui {

class GlfwApplication {
public:

    GlfwApplication(std::string title, int width = 1280, int height = 720);
    ~GlfwApplication();

    // Wird jeden Frame zwischen ImGui::NewFrame() und ImGui::Render() aufgerufen.
    // Hier rein kommt der eigentliche UI-Code (ImGui::Begin/.../End etc.)
    void set_drawable(DrawablePtr plot) { _plot_object = plot; }

    void run();

private:
    void init_window(const std::string& title, int width, int height);
    void init_imgui();
    void shutdown();

    GLFWwindow* window_ = nullptr;
    DrawablePtr _plot_object;
};

};

