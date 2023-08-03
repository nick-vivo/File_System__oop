cmake_minimum_required(VERSION 3.27.1)

project(File_System CXX)

#add STL
add_subdirectory(modules/STL)

#library objects
set(OBJECT_LIB "include/object.h" "src/object.cc")
add_library(object ${OBJECT_LIB})
target_include_directories(object PUBLIC "include" "modules/STL/include")
target_link_libraries(object tools string)

#library file_system
set(FILE_SYSTEM_LIB "include/file_system.h" "src/file_system.cc")
add_library(file_system ${FILE_SYSTEM_LIB})
target_include_directories(file_system PUBLIC "include")
target_link_libraries(file_system object)

#test.cpp
# add_executable(test test.cpp)
# target_include_directories(object PUBLIC "include" "modules/STL/include")
# target_link_libraries(test file_system)

#library menu
set(MENU_LIB "modules/menu/menu.cc")
add_library(menu ${MENU_LIB})
target_include_directories(menu PUBLIC "include")
target_link_libraries(menu string)

#tests
add_subdirectory(tests/googletest)
set(G_TESTSING gmock_main gmock gtest gtest_main)

add_executable(g_test tests/g_test.cpp)
target_include_directories(g_test PUBLIC "include" "tests/googletest/googlemock/include" "tests/googletest/googletest/include")
target_link_libraries(g_test ${G_TESTSING} object file_system)

#app
set(OUT_EXE "src/out.cpp")
add_executable(out ${OUT_EXE})
target_include_directories(out PUBLIC "include" "modules/menu")
target_link_libraries(out menu string file_system)