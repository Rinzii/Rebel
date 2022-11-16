#pragma once
#include <memory>
#include <utility>
#include "platform/window.hpp"
#include "rendering/renderer.hpp"

namespace rebel
{
    class ServiceLocator
    {
    public:
        static inline const std::unique_ptr<Window> &GetWindow() { return m_window; }
        static inline const std::unique_ptr<Renderer> &GetRenderer() { return m_renderer; }
        static inline void Provide(Window *window)
        {
            if (m_window != nullptr) return;
            m_window = std::unique_ptr<Window>(window);
        }

        static inline void Provide(Renderer* renderer, RendererSettings settings)
        {
            if (m_renderer != nullptr) return;

            m_renderer = std::unique_ptr<Renderer>(renderer);
            m_renderer->Init(std::move(settings));
        }

        static inline void ShutdownServices()
        {
            // ensure we shut down services in the correct order
            // usually opposite order of initialized.
            shutdownRenderer();
            shutdownWindow();
        }

    private:

        static inline std::unique_ptr<Window> m_window = nullptr;
        static inline std::unique_ptr<Renderer> m_renderer = nullptr;

        static inline void shutdownWindow()
        {
            m_window.reset();
            m_window = nullptr;
        }

        static inline void shutdownRenderer()
        {
            if (!m_renderer) return;

            m_renderer->Shutdown();
            m_renderer = nullptr;
        }

    };
}