#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <rebel/engine/rendering/renderer.hpp>

namespace rebel
{
    class VulkanRenderer : public Renderer
    {

        // Functions
    public:
        void Init(RendererSettings settings) override;
        void Shutdown() override;
        void BeginFrame() override;

    private:
        void InitVulkanCore();
        void CreateSwapchain();
        void CreateCommands();
        void CreateDefaultRenderPass();
        void CreateFramebuffers();
        void CreateSyncStructures();


        // Members
    private:
        //TODO: TEMPORARY FRAME NUMBER
        uint64_t m_frameNumber { 0 };

        RendererSettings m_rendererSettings {};

        // Vulkan Core
        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debug_messenger;
        VkPhysicalDevice m_physicalDevice;   // physical device
        VkDevice m_device;                   // logical device
        VkSurfaceKHR m_surface;

        // Swap chain
        VkSwapchainKHR m_swapchain;
        VkFormat m_swapchainImageFormat;
        std::vector<VkImage> m_swapchainImages;
        std::vector<VkImageView> m_swapchainImageViews;
        VkExtent2D m_windowExtent;

        // Command Pools and Queues
        VkQueue m_graphicsQueue;
        uint32_t m_graphicsQueueFamily;

        VkCommandPool m_commandPool;
        VkCommandBuffer m_mainCommandBuffer;

        // Render pass
        VkRenderPass m_renderPass;
        std::vector<VkFramebuffer> m_framebuffers {3};

        // Synchronization Objects
        VkSemaphore m_presentSemaphore, m_renderSemaphore;
        VkFence m_renderFence;
    };
}


