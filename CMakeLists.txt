# Main

cmake_minimum_required(VERSION 3.5)
project(SuperMarioBros-SFML LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/MP)
endif()

# Dependencies
include(Dependencies.cmake)

# Projects
add_subdirectory(Core)
add_subdirectory(SuperMarioBros)
