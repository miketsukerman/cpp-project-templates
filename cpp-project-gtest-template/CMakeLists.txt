cmake_minimum_required(VERSION 3.10)

project(cpp-project-template VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

add_library(sample SHARED source/sample.cpp)
target_compile_features(sample PUBLIC cxx_std_20)
target_include_directories(sample PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)
set_property(TARGET sample PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET sample PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

add_executable(sample_app source/main.cpp)
target_compile_features(sample_app PUBLIC cxx_std_20)
target_link_libraries(sample_app PRIVATE sample)

add_executable(sample_test test/test.cpp)
target_compile_features(sample_test PUBLIC cxx_std_20)
target_link_libraries(sample_test PRIVATE GTest::GTest sample spdlog::spdlog)

enable_testing()
include(GoogleTest)
gtest_add_tests(TARGET sample_test)