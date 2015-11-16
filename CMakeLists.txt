project(Falcon.Fold)

cmake_minimum_required(VERSION 2.8)

if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR CMAKE_COMPILER_IS_GNUCXX)
  include(CMakeDefinitions.txt)
  #add_definitions(-g)
  add_definitions(-std=c++14)
endif()

include_directories(.)

add_executable(fold_test test/fold_test.cpp)

enable_testing()

add_test(fold_test fold_test)

install ( DIRECTORY ${PROJECT_SOURCE_DIR}/falcon-fold
          DESTINATION .
        )
