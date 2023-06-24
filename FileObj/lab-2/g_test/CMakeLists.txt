cmake_minimum_required(VERSION 3.26.4)

project(g_test)

add_subdirectory(googletest)

add_executable(g_test g_test.cpp)

target_link_libraries(g_test gtest_main gmock_main)
