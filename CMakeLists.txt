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
add_executable(test test.cpp)
target_include_directories(object PUBLIC "include" "modules/STL/include")
target_link_libraries(test object)