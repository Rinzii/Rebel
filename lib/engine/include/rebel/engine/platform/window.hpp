#pragma once
#include <string>
#include <unordered_map>
#include <any>
#include <tuple>

namespace rebel
{
    enum class SurfaceArgs
    {
        INSTANCE,
       ALLOCATORS,
       OUT_SURFACE
    };

    struct WindowData
    {
        std::string title;
        uint32_t width, height;
    };

    class Window
    {
    public:
        virtual void InitWindow(WindowData data) = 0;
        virtual bool Update() = 0;

        virtual std::pair<int, int> GetWindowExtent() = 0;
        virtual void GetDrawSurface(std::unordered_map<SurfaceArgs, std::any>) = 0;
    };
}
