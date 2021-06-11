cmake_minimum_required(VERSION 3.10)

project(cpp-project-template VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(THRIFT_GENERATOR "Path to apache thrift code generator")

if(NOT THRIFT_GENERATOR) 
    message(FATAL_ERROR "You have to provide THRIFT_GENERATOR parameter to cmake")
endif()

find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(Thrift REQUIRED)

add_custom_command(
    COMMAND ${THRIFT_GENERATOR} --gen cpp -o ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/idl/sample.thrift
    OUTPUT 
        ${CMAKE_BINARY_DIR}/gen-cpp/sample_types.h
        ${CMAKE_BINARY_DIR}/gen-cpp/SampleService.h
        ${CMAKE_BINARY_DIR}/gen-cpp/SampleService.cpp 
        ${CMAKE_BINARY_DIR}/gen-cpp/SampleService_server.skeleton.cpp
)

add_library(sample SHARED 
    source/sample.cpp
    ${CMAKE_BINARY_DIR}/gen-cpp/SampleService.cpp 
)
target_compile_features(sample PUBLIC cxx_std_20)
target_include_directories(sample PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/gen-cpp>
    )
set_property(TARGET sample PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET sample PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(sample PUBLIC thrift::thrift)

add_executable(sample_server source/server/main.cpp)
target_compile_features(sample_server PUBLIC cxx_std_20)
target_link_libraries(sample_server PRIVATE sample)

add_executable(sample_app source/client/main.cpp)
target_compile_features(sample_app PUBLIC cxx_std_20)
target_link_libraries(sample_app PRIVATE sample)

add_executable(sample_test test/test.cpp)
target_compile_features(sample_test PUBLIC cxx_std_20)
target_link_libraries(sample_test PRIVATE Catch2::Catch2 sample spdlog::spdlog)

include(CTest)
include(Catch)
catch_discover_tests(sample_test)