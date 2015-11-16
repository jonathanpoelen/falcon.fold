project(Falcon.Fold)

cmake_minimum_required(VERSION 2.8)

include(CMakeDefinitions.txt)
include_directories(.)
#add_definitions(-g)
add_definitions(-std=c++14)

add_executable(fold_test test/fold_test.cpp)

enable_testing()

add_test(fold_test fold_test)
