cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")

set(target_prefix rebel)

project(rebel)

set(is_root_project OFF)

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(is_root_project ON)
endif()

############################################################################################################
#
# Find and create Vulkan
#
############################################################################################################

# AUTO_LOCATE_VULKAN - accepted value ON or OFF
# ON  - Use CMake to auto locate the Vulkan SDK.
# OFF - Vulkan SDK path can be specified manually. This is helpful to test the build on various Vulkan version.
option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if(AUTO_LOCATE_VULKAN)
  message(STATUS "Attempting auto locate Vulkan using CMake......")

  # Find Vulkan Path using CMake's Vulkan Module
  # This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
  # Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
  find_package(Vulkan)

  # Try extracting VulkanSDK path from ${Vulkan_INCLUDE_DIRS}
  if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
    set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
    STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
  endif()

  if(NOT Vulkan_FOUND)
    # CMake may fail to locate the libraries but could be able to
    # provide some path in Vulkan SDK include directory variable
    # 'Vulkan_INCLUDE_DIRS', try to extract path from this.
    message(STATUS "Failed to locate Vulkan SDK, retrying again...")
    if(EXISTS "${VULKAN_PATH}")
      message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
    else()
      message("Error: Unable to locate Vulkan SDK. Please turn off auto locate option by specifying 'AUTO_LOCATE_VULKAN' as 'OFF'")
      message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt.")
      return()
    endif()
  endif()
else()
  message(STATUS "Attempting to locate Vulkan SDK using manual path......")
  set(VULKAN_SDK "C:/VulkanSDK")
  set(VULKAN_VERSION "1.0.33.0")
  set(VULKAN_PATH "${VULKAN_SDK}/${VULKAN_VERSION}")
  message(STATUS "Using manual specified path: ${VULKAN_PATH}")

  # Check if manual set path exists
  if(NOT EXISTS "${VULKAN_PATH}")
    message("Error: Unable to locate this Vulkan SDK path VULKAN_PATH: ${VULKAN_PATH}, please specify correct path.
		For more information on correct installation process, please refer to subsection 'Getting started with Lunar-G SDK'
		and 'Setting up first project with CMake' in Chapter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469809.")
    return()
  endif()
endif()

# Add any required preprocessor definitions here
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

# vulkan-1 library for build Vulkan application.
set(VULKAN_LIB_LIST "vulkan-1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  # Include Vulkan header files from Vulkan SDK
  include_directories(AFTER ${VULKAN_PATH}/Include)

  # Link directory for vulkan-1
  link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)
endif()


# Define directories and the contained folder and files inside.
if(WIN32)
  source_group("include" REGULAR_EXPRESSION "include/*")
  source_group("source" REGULAR_EXPRESSION "source/*")
endif(WIN32)

# Define include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Gather list of header and source files for compilation
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)


############################################################################################################



option(REBEL_BUILD_SHADERS "Build rebel shaders" ${is_root_project})
option(REBEL_PCH "Use PCH" OFF)
option(REBEL_BUILD_EXE "Build rebel application (else only library)" ${is_root_project})

if(REBEL_BUILD_EXE AND REBEL_BUILD_SHADERS)
  find_program(glslc glslc)

  if(glslc STREQUAL glslc-NOTFOUND)
    message(WARNING "glslc not found, disabling REBEL_BUILD_SHADERS")
    set(REBEL_BUILD_SHADERS OFF CACHE STRING "" FORCE)
  endif()
endif()

add_subdirectory(tools/embed_shader)
add_subdirectory(lib)

if(REBEL_BUILD_EXE AND REBEL_BUILD_SHADERS)
  message(STATUS "Adding build step to embed shaders")
  add_custom_command(
    DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/triangle.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/triangle.frag

    OUTPUT
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bin/triangle_vert.spv.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bin/triangle_frag.spv.hpp

    COMMAND embed-shader ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/triangle.vert > ${CMAKE_CURRENT_SOURCE_DIR}/src/bin/triangle_vert.spv.hpp
    COMMAND embed-shader ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/triangle.frag > ${CMAKE_CURRENT_SOURCE_DIR}/src/bin/triangle_frag.spv.hpp
  )
endif()

if(REBEL_BUILD_EXE)
  add_executable(${PROJECT_NAME})

  target_sources(${PROJECT_NAME} PRIVATE
    ${CPP_FILES}
    ${HPP_FILES}
    src/main.cpp

    src/bin/triangle_vert.spv.hpp
    src/bin/triangle_frag.spv.hpp
  )

  target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${VULKAN_LIB_LIST}

    PRIVATE
    rebel::engine
    rebel::compile-options
  )

  string(TOUPPER ${target_prefix} target_prefix_upper)

  if(${${target_prefix_upper}_PCH})
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ${target_prefix}-vk)
  endif()

  target_include_directories(${PROJECT_NAME} PRIVATE src)
endif()


############################################################################################################
# References

# PUBLIC
# $<INSTALL_INTERFACE:include>
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# glm
# nlohmann_json
#
# # TODO: investigate moving entt out of the public exposure land
# EnTT
# PRIVATE
# ${CMAKE_CURRENT_SOURCE_DIR}/src
# #${Vulkan_INCLUDE_DIRS}
# SDL2main
# SDL2-static
# glfw
# vk-bootstrap
# vma
# stb
# spirv_cross
# assimp
# fmt
#
#
# PUBLIC
# glm
# nlohmann_json
#
# # TODO: investigate moving entt out of the public exposure land
# EnTT
# PRIVATE
# ${Vulkan_LIBRARIES}
# SDL2main
# SDL2-static
# glfw
# vk-bootstrap
# vma
# spirv-cross-core
# spirv-cross-glsl
# assimp
# fmt