cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)
project(Engine VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

file(GLOB ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/*.cpp

)

add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/libs/glad244/src/gl.c)
target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/glad244/include/)

add_library(stb STATIC
    ${CMAKE_SOURCE_DIR}/libs/stb/stb.cpp)
target_include_directories(stb PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/stb)


add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering)

target_link_libraries(Engine PUBLIC glad glfw glm stb imgui)