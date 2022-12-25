cmake_minimum_required(VERSION 3.23)
project(IEML)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE src "lib/*.hpp" "lib/*.cpp")

add_subdirectory(modules/template_regex)

add_executable(${PROJECT_NAME} ${src} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE modules)
