#pragma once

#include <rebel/engine/platform/window.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace rebel
{
    class RWindow : public Window
    {
    public:
        RWindow();

        void InitWindow(WindowData data) override;

        bool Update() override;

        std::pair<int, int> GetWindowExtent() override;
        void GetDrawSurface(std::unordered_map<SurfaceArgs, std::any> args) override;

    private:
        GLFWwindow *m_window;
    };
}