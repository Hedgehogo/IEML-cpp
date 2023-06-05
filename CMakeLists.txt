cmake_minimum_required(VERSION 3.23)
project(IEML_cpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

set(ABSL_PROPAGATE_CXX_STD ON)

set(ABSL_ENABLE_INSTALL ON)


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
        abseil
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp
        GIT_TAG        lts_2023_01_25
        FIND_PACKAGE_ARGS NAMES absl
)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
        FIND_PACKAGE_ARGS NAMES GTest
)

FetchContent_MakeAvailable(ctre option_result_cpp abseil googletest)


file(GLOB_RECURSE src "lib/*.hpp" "lib/*.cpp")

add_library(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME} PUBLIC option_result_cpp absl::flat_hash_map)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<BUILD_INTERFACE:${ctre_SOURCE_DIR}/include>
        )

add_executable(${PROJECT_NAME}_ex main.cpp)

target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})


file(GLOB_RECURSE test_src "tests/*.hpp" "tests/*.cpp")

add_executable(${PROJECT_NAME}_tests ${test_src})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest gtest_main ${PROJECT_NAME})


install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/IEML DESTINATION ${CMAKE_INSTALL_PREFIX}/include PATTERN "*.hpp")

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}Config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
        )