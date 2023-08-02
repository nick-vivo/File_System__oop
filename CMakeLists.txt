cmake_minimum_required(VERSION 3.27.1)

project(File_System CXX)

#add STL
add_subdirectory(modules/STL)

#library objects
set(OBJECT_LIB "include/object.h" "src/object.cc")
add_library(object ${OBJECT_LIB})
target_include_directories(object PUBLIC "include" "modules/STL/include")
