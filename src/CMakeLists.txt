cmake_minimum_required(VERSION 3.19)

add_library(FGengine SHARED main.cpp)
add_compile_options(-fPIC)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(window)
add_subdirectory(shaders)

target_link_libraries(FGengine SDL2 GL GLEW)