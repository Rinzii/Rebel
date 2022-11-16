if("${target_prefix}" STREQUAL "")
  message(FATAL_ERROR "target_prefix unset")
endif()

project(${target_prefix}-engine VERSION ${${target_prefix}_version})

configure_file(src/build_version.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/include/${target_prefix}/build_version.hpp" @ONLY)

add_library(${PROJECT_NAME})
add_library(${target_prefix}::engine ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  include
  "${CMAKE_CURRENT_BINARY_DIR}/include"

  PRIVATE
  src
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${target_prefix}::vk
  glfw::glfw

  PRIVATE
  #${target_prefix}::compile-options
)

string(TOUPPER ${target_prefix} target_prefix_upper)


target_sources(${PROJECT_NAME}
  PUBLIC
  include/${target_prefix}/engine/service_locator.hpp

  include/${target_prefix}/engine/platform/engine.hpp
  include/${target_prefix}/engine/platform/entry_point.hpp
  include/${target_prefix}/engine/platform/window.hpp

  include/${target_prefix}/engine/rendering/renderer.hpp

  PRIVATE
  src/platform/engine.cpp
  src/platform/rebel_window.hpp
  src/platform/rebel_window.cpp


)
