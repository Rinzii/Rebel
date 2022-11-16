#pragma once
#include <iostream>

// Helper macro for vulkan error checking
using namespace std;
#define VK_CHECK(x)                                                             \
    do {                                                                        \
        VkResult err = x;                                                       \
        if (err) {                                                              \
            std::cout << "Detected Vulkan error: " << err << std::endl;         \
            abort();                                                            \
        }                                                                       \
    } while(0)


class VulkanUtilities {

};