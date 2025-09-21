# SuperMarioBros

file(GLOB SOURCES src/*.cpp src/*.hpp)
add_executable(SuperMarioBros ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(SuperMarioBros Core)

target_include_directories(SuperMarioBros PRIVATE src)

# Working directory for VS Debug
set_target_properties(SuperMarioBros PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/SuperMarioBros"
)
