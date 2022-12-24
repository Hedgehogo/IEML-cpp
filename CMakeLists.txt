cmake_minimum_required(VERSION 3.23)
project(IEML)

file(GLOB_RECURSE src "lib/*.hpp" "lib/*.cpp")

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${src} main.cpp)
