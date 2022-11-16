#include "rebel_window.hpp"
#include <iostream>

namespace rebel
{
    RWindow::RWindow()
    {
        m_window = nullptr;
    }

    void RWindow::InitWindow(WindowData data)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(static_cast<int>(data.width),
                                    static_cast<int>(data.height),
                                    data.title.c_str(),
                                    nullptr,
                                    nullptr);
    }

    bool RWindow::Update()
    {
        glfwPollEvents();

        return glfwWindowShouldClose(m_window);
    }

    std::pair<int, int> RWindow::GetWindowExtent()
    {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        return {width, height};
    }

    void RWindow::GetDrawSurface(std::unordered_map<SurfaceArgs, std::any> args)
    {
        try
        {
            auto instance = std::any_cast<VkInstance>(args[SurfaceArgs::INSTANCE]);
            auto *allocators = args[SurfaceArgs::ALLOCATORS].has_value() ?
                                        std::any_cast<VkAllocationCallbacks *>(args[SurfaceArgs::ALLOCATORS]) : nullptr;
            auto *outSurface = std::any_cast<VkSurfaceKHR *>(args[SurfaceArgs::OUT_SURFACE]);

            if (instance == VK_NULL_HANDLE)
            {
                throw std::runtime_error("A valid instance is required");
            }

            if (glfwCreateWindowSurface(instance, m_window, allocators, outSurface) != VK_SUCCESS)
            {
                    throw std::runtime_error("Failed to create window surface");
            }
        }
        catch (std::bad_any_cast& e)
        {
            std::cout << "Failed to cast window surface arguments:" << e.what() << '\n';
        }
    }
}