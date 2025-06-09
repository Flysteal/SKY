cmake_minimum_required(VERSION 4.0.0)
project(imgui)

# ImGui core sources
set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
)

# ImGui backends (add or remove as needed)
set(IMGUI_BACKENDS
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_BACKENDS}
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)
target_link_libraries(imgui PUBLIC glfw)


target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
