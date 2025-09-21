# Core

file(GLOB SOURCES src/Core/*.cpp src/Core/*.hpp)
add_library(Core STATIC ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

# SFML
target_link_libraries(Core SFML::Graphics)
target_link_libraries(Core SFML::Audio)

target_include_directories(Core PUBLIC "src")
