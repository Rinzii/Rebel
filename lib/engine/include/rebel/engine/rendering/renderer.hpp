#pragma once
#include <string>

namespace rebel
{
    struct RendererSettings
    {
        std::string ApplicationName;
        bool EnableValidationLayers;
    };
    class Renderer
    {
    public:
        virtual void Init(RendererSettings) = 0;
        virtual void Shutdown() = 0;
        virtual void BeginFrame() = 0;
    };
}