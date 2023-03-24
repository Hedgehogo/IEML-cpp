cmake_minimum_required(VERSION 3.23)
project(IEML_cpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE src "lib/*.hpp" "lib/*.cpp")

add_subdirectory(modules/compile_time_regex)

add_library(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PRIVATE modules/compile_time_regex/include)

add_executable(${PROJECT_NAME}_ex main.cpp)

target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})
