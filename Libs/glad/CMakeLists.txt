cmake_minimum_required(VERSION 3.15)

project(glad VERSION 0.1.0 LANGUAGES C)

add_library(glad STATIC src/gl.c)

target_include_directories(glad
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(UNIX AND NOT APPLE)
    target_link_libraries(glad PUBLIC dl)
endif()

target_compile_features(glad PUBLIC c_std_99)

# Optional: if you want to support installing glad
# install(TARGETS glad
#     EXPORT gladTargets
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib
#     RUNTIME DESTINATION bin
#     INCLUDES DESTINATION include
# )
# install(DIRECTORY include/ DESTINATION include)
# install(EXPORT gladTargets FILE gladTargets.cmake NAMESPACE glad:: DESTINATION lib/cmake/glad)
