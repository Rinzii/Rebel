if("${target_prefix}" STREQUAL "")
    message(FATAL_ERROR "target_prefix unset")
endif()

project(${target_prefix}-vk)

add_library(${PROJECT_NAME})
add_library(${target_prefix}::vk ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include

        PRIVATE
        src
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${target_prefix}::engine
        VulkanMemoryAllocator
        ${target_prefix}::util
        vk-bootstrap

        PRIVATE
        ${Vulkan_LIBRARIES}
        vk-bootstrap
        VulkanMemoryAllocator
        spirv-cross-glsl
        )

string(TOUPPER ${target_prefix} target_prefix_upper)


target_sources(${PROJECT_NAME} PRIVATE
        include/${target_prefix}/vk/spir_v.hpp
        include/rebel/vk/vulkan_initializers.hpp
        include/rebel/vk/vulkan_renderer.hpp
        include/rebel/vk/vulkan_types.hpp
        include/rebel/vk/vulkan_utilities.hpp

        src/spir_v.cpp
        src/vulkan_initializers.cpp
        src/vulkan_renderer.cpp

        )
