#include <rebel/engine/platform/engine.hpp>
#include <rebel/engine/service_locator.hpp>
#include <utility>
#include <rebel/vk/vulkan_renderer.hpp>
#include "rebel_window.hpp"

namespace rebel
{
	Engine::Engine() : Engine("Rebel Engine") {}

	Engine::Engine(std::string windowTitle) : m_windowTitle(std::move(windowTitle)), m_isRunning(true)
    {
        InitializeServices();
    }

	Engine::~Engine()
    {
        DestroyServices();
    }


    void Engine::Run()
    {


        // Begin the main game loop
        while (m_isRunning)
        {
            // Update the window
            if (ServiceLocator::GetWindow()->Update()) {
                m_isRunning = false;
                continue;
            }

            // Calculate delta time

            // Update game state
            Update(0.0f); // This currently is a placeholder

            // Update physics


            // Draw
            ServiceLocator::GetRenderer()->BeginFrame();
        }
    }


    void Engine::InitializeServices()
    {
        // provide a window
        ServiceLocator::Provide(new RWindow());

        // Initialize the window
        ServiceLocator::GetWindow()->InitWindow({
                                                        .title = m_windowTitle,
                                                        .width = 1280,
                                                        .height = 720
                                                });

        // initialize input system


        // initialize the renderer
        RendererSettings settings
        {
                .ApplicationName = m_windowTitle,
                .EnableValidationLayers = true
        };

        ServiceLocator::Provide(new VulkanRenderer(), settings);
    }

    void Engine::DestroyServices()
    {
        ServiceLocator::ShutdownServices();
    }

}
