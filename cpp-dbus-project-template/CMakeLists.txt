cmake_minimum_required(VERSION 3.10)

project(cpp-project-template VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(DBus1 REQUIRED)

add_library(sample SHARED source/sample.cpp)
target_compile_features(sample PUBLIC cxx_std_20)
target_include_directories(sample PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)
set_property(TARGET sample PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET sample PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

add_executable(sample_app source/main.cpp)
target_compile_features(sample_app PUBLIC cxx_std_20)
target_link_libraries(sample_app PRIVATE sample dbus-1::dbus-1)

add_executable(sample_test test/test.cpp)
target_compile_features(sample_test PUBLIC cxx_std_20)
target_link_libraries(sample_test PRIVATE Catch2::Catch2 sample spdlog::spdlog)

include(CTest)
include(Catch)
catch_discover_tests(sample_test)