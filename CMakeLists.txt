cmake_minimum_required(VERSION 3.12)

project(roguelike)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

find_package(BearLibTerminal REQUIRED)
include_directories(SYSTEM ${BLT_INCLUDE_DIRS})

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)


add_executable(roguelike ${HEADERS} ${SOURCES} src/game/systems/reading_file_levels_system.cpp include/game/systems/reading_file_levels_system.h src/game/systems/creating_entity_system.cpp include/game/systems/creating_entity_system.h src/game/scenes/game_lv3_scene.cpp include/game/scenes/game_lv3_scene.h src/game/systems/generate_random_map_system.cpp include/game/systems/generate_random_map_system.h)

include_directories(${PROJECT_HEADERS_DIR} )

target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARIES})

file(COPY ${BLT_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add linting before compilation
include(CppLint)
ADD_STYLE_CHECK_TARGET(lint ${PROJECT_NAME} ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})
add_dependencies(${PROJECT_NAME} lint)
