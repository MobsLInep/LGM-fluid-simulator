cmake_minimum_required(VERSION 3.21)
project(lbm-fluid-simulator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(lbm-fluid-simulator
    src/main.cpp
    src/gpu/gpu_context.cpp
    src/gpu/buffer_manager.cpp
    src/gpu/compute_pipeline.cpp
    src/gpu/renderer.cpp
    src/core/application.cpp
    src/simulation/grid.cpp
    src/simulation/lbm_simulator.cpp
    src/ui/visualization.cpp
)

target_include_directories(lbm-fluid-simulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (MSVC)
    target_compile_options(lbm-fluid-simulator PRIVATE /W4 /permissive-)
    target_link_libraries(lbm-fluid-simulator PRIVATE gdi32)
else()
    target_compile_options(lbm-fluid-simulator PRIVATE -Wall -Wextra -Wpedantic -O3)
    target_link_libraries(lbm-fluid-simulator PRIVATE gdi32)
endif()

option(ENABLE_WEBGPU "Enable WebGPU + GLFW integration" OFF)
if (ENABLE_WEBGPU)
    message(STATUS "WebGPU integration requested")
    # Placeholder find_package blocks; disabled by default to avoid configure failures.
    # find_package(glfw3 REQUIRED)
    # find_package(wgpu REQUIRED)
    # target_link_libraries(lbm-fluid-simulator PRIVATE glfw wgpu)
endif()

include(CTest)
enable_testing()

add_executable(test-vector tests/test_vector.cpp)
target_include_directories(test-vector PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_test(NAME test_vector COMMAND test-vector)

add_executable(test-validation tests/test_validation.cpp)
target_include_directories(test-validation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_sources(test-validation PRIVATE
    src/simulation/grid.cpp
    src/simulation/lbm_simulator.cpp
    src/gpu/buffer_manager.cpp
)
add_test(NAME test_validation COMMAND test-validation)

add_executable(test-poiseuille tests/test_poiseuille.cpp)
target_include_directories(test-poiseuille PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_sources(test-poiseuille PRIVATE
    src/simulation/grid.cpp
    src/simulation/lbm_simulator.cpp
    src/gpu/buffer_manager.cpp
)
add_test(NAME test_poiseuille COMMAND test-poiseuille)

