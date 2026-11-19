cmake_minimum_required(VERSION 3.16)
project(lab3_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Enable gcov/lcov coverage flags" OFF)

set(LAB3_SOURCES
    src/DynamicArray.cpp
    src/SinglyList.cpp
    src/DoublyList.cpp
    src/Stack.cpp
    src/Queue.cpp
    src/HashTable.cpp
    src/CompleteBinaryTree.cpp
    src/Serializer.cpp
    src/TextSerializer.cpp
)

add_library(lab3_core STATIC ${LAB3_SOURCES})
target_include_directories(lab3_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(lab3_core PRIVATE -Wall -Wextra -Wpedantic)

if(ENABLE_COVERAGE)
    target_compile_options(lab3_core PUBLIC --coverage -O0 -g)
    target_link_options(lab3_core PUBLIC --coverage)
endif()

find_package(GTest QUIET)
if(GTest_FOUND)
    add_executable(run_google tests/tests_google.cpp)
    target_link_libraries(run_google PRIVATE lab3_core GTest::gtest_main)
endif()

find_package(Boost QUIET COMPONENTS unit_test_framework)
if(Boost_FOUND)
    add_executable(run_boost tests/tests_boost.cpp)
    target_link_libraries(run_boost PRIVATE lab3_core)
endif()

find_package(Catch2 3 QUIET)
if(Catch2_FOUND)
    add_executable(run_catch2 tests/tests_catch2.cpp)
    target_link_libraries(run_catch2 PRIVATE lab3_core Catch2::Catch2WithMain)
endif()

find_package(benchmark QUIET)
if(benchmark_FOUND)
    add_executable(run_bench bench/bench_main.cpp)
    target_link_libraries(run_bench PRIVATE lab3_core benchmark::benchmark)
endif()
