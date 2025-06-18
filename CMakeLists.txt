cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)
project(SkyLands VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Libs/glad)
add_subdirectory(Libs/glfw)
add_subdirectory(Libs/glm)
add_subdirectory(Libs/imgui)

add_subdirectory(Engine)
add_subdirectory(Game)

add_custom_target(runGame
COMMAND $<TARGET_FILE:Game>
DEPENDS Game
WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})