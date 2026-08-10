cmake_minimum_required(VERSION 3.16)
project(Geometry2D VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(geometry2d src/geometry.cpp)
target_include_directories(geometry2d PUBLIC include)
target_compile_options(geometry2d PRIVATE -Wall -Wextra -Wpedantic)

add_executable(geometry_demo app/main.cpp)
target_link_libraries(geometry_demo PRIVATE geometry2d)

include(CTest)
if(BUILD_TESTING)
    add_executable(geometry_tests tests/geometry_tests.cpp)
    target_link_libraries(geometry_tests PRIVATE geometry2d)
    add_test(NAME geometry_tests COMMAND geometry_tests)
endif()
