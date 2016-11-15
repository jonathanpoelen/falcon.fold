project(Falcon.Fold)

cmake_minimum_required(VERSION 2.8)

option(FALCON_FOLD_ENABLE_CXX17 "enable -std=c++1z if clang or gcc." OFF)

if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR CMAKE_COMPILER_IS_GNUCXX)
  include(CMakeDefinitions.txt)
  if (FALCON_FOLD_ENABLE_CXX17)
    add_definitions(-std=c++1z -DFALCON_CXX_HAS_FEATURE_FOLD_EXPRESSIONS=1)
  else()
    add_definitions(-std=c++14)
  endif()
endif()

add_definitions(-DBRIGAND_NO_BOOST_SUPPORT)

include_directories(.)
include_directories(modules/falcon.cxx/include/)

add_executable(fold_test test/fold_test.cpp)

enable_testing()

add_test(fold_test fold_test)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/falcon-fold DESTINATION .)
