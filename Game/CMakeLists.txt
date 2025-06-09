cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)
project(Game VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

file(GLOB GAME_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_executable(Game ${GAME_SOURCES})

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/include
    # ${CMAKE_SOURCE_DIR}/engine/include/rendering
    ${GLFW_INCLUDE_DIRS}
    ${GLAD_INCLUDE_DIRS}

)

target_link_libraries(Game PRIVATE Engine)