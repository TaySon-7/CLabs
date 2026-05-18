cmake_minimum_required(VERSION 3.14)
project(GraphLab C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Скачиваем GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(graph_lib func.c)
target_include_directories(graph_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(graph_demo main.c)
target_link_libraries(graph_demo graph_lib)

# Исполняемый файл с тестами
add_executable(test_graph
        test_graph.cpp
)

target_link_libraries(test_graph graph_lib GTest::gtest_main)

add_executable(graph_benchmark benchmark.c)
target_link_libraries(graph_benchmark graph_lib)

include(GoogleTest)
gtest_discover_tests(test_graph)
