cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)
project(SkyLands VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Libs/glad)
add_subdirectory(Libs/glfw)
add_subdirectory(Libs/glm)
add_subdirectory(Libs/imgui)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_NO_EXPORT ON)
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)

add_subdirectory(Libs/assimp)


add_subdirectory(Engine)
add_subdirectory(Game)

add_custom_target(runGame
COMMAND $<TARGET_FILE:Game>
DEPENDS Game
WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})