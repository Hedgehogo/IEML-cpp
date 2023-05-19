cmake_minimum_required(VERSION 3.23)
project(IEML_cpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)


FetchContent_Declare(
        ctre
        GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions.git
        GIT_TAG        main
        FIND_PACKAGE_ARGS NAMES ctre
)

FetchContent_Declare(
        option_result_cpp
        GIT_REPOSITORY https://github.com/Hedgehogo/option-result-cpp.git
        GIT_TAG        main
        FIND_PACKAGE_ARGS NAMES option_result_cpp
)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG        v1.13.0
        FIND_PACKAGE_ARGS NAMES googletest
)

FetchContent_MakeAvailable(ctre option_result_cpp googletest)


file(GLOB_RECURSE src "lib/*.hpp" "lib/*.cpp")

add_library(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} PUBLIC option_result_cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${ctre_SOURCE_DIR}/include ${option_result_cpp_SOURCE_DIR}/lib)


add_executable(${PROJECT_NAME}_ex main.cpp)

target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_ex PRIVATE lib/)


file(GLOB_RECURSE test_src "tests/*.hpp" "tests/*.cpp")

add_executable(${PROJECT_NAME}_tests ${test_src})

target_include_directories(${PROJECT_NAME}_tests PRIVATE lib/)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest gtest_main ${PROJECT_NAME})
