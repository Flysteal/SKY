cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)
project(SkyLands VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(engine)
add_subdirectory(game)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)
add_subdirectory(libs/imgui)


add_custom_target(runGame
COMMAND $<TARGET_FILE:Game>
DEPENDS Game
WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})