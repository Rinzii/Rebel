if("${target_prefix}" STREQUAL "")
    message(FATAL_ERROR "target_prefix unset")
endif()

project(${target_prefix}-util)

find_package(Threads)

add_library(${PROJECT_NAME})
add_library(${target_prefix}::util ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include

        PRIVATE
        src
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        fmt::fmt
        glm::glm
        ${target_prefix}::interface

        PRIVATE
        ${target_prefix}::stb-image
        ${target_prefix}::compile-options

        Threads::Threads
        )

string(TOUPPER ${target_prefix} target_prefix_upper)

if(${${target_prefix_upper}_PCH})
    target_precompile_headers(${PROJECT_NAME} PRIVATE
            <fmt/format.h>
            <algorithm>
            <atomic>
            <functional>
            <memory>
            <mutex>
            <string>
            <vector>
            <unordered_map>
            )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        GLM_FORCE_XYZW_ONLY
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_FORCE_SILENT_WARNINGS
        GLM_ENABLE_EXPERIMENTAL
        GLM_EXT_INCLUDED
        )

target_sources(${PROJECT_NAME} PRIVATE
  include/${target_prefix}/util/mufo.hpp
  include/${target_prefix}/util/error.hpp
  include/${target_prefix}/util/version.hpp

    src/version.cpp
)
