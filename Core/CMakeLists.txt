# Core

file(GLOB SOURCES src/Core/*.cpp src/Core/*.hpp)
add_library(Core STATIC ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

# SFML
target_link_libraries(Core PUBLIC SFML::Graphics)
target_link_libraries(Core PUBLIC SFML::Audio)

# yaml-cpp
target_link_libraries(Core PUBLIC yaml-cpp::yaml-cpp)

target_include_directories(Core PUBLIC "src")
