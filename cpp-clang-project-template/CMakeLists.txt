cmake_minimum_required(VERSION 3.10)

project(cpp-project-template VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)

set(LLVM_BASE_DIR "/usr/lib/llvm-${LLVM_VERSION}")
set(LLVM_DIR "${LLVM_BASE_DIR}/lib/cmake/llvm")
set(Clang_DIR "${LLVM_BASE_DIR}/lib/cmake/clang")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Clang_DIR} ${LLVM_DIR})

include(AddLLVM)
include(AddClang)

add_custom_target(clang-resource-headers )

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CLANG_LIBS
        clangFrontend
        clangSerialization
        clangDriver
        clangSerialization
        clangCodeGen
        clangParse
        clangSema
        clangStaticAnalyzerFrontend
        clangStaticAnalyzerCheckers
        clangStaticAnalyzerCore
        clangAnalysis
        clangARCMigrate
        clangRewrite
        clangRewriteFrontend
        clangAnalysis
        clangAST
        clangBasic
        clangEdit
        clangLex
        clangTooling
        clangToolingSyntax
        clangFrontendTool
        clangFrontend
        clangBasic
        clangASTMatchers
        )

add_library(sample source/sample.cpp)
target_compile_features(sample PUBLIC cxx_std_20)
target_include_directories(sample PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)

target_include_directories(sample PUBLIC ${LLVM_BASE_DIR}/include)
target_link_directories(sample PUBLIC ${LLVM_BASE_DIR}/lib)
target_link_libraries(sample PUBLIC ${LLVM_LIBS} ${CLANG_LIBS})

set_property(TARGET sample PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET sample PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

add_clang_tool(sample_app source/main.cpp)
target_compile_features(sample_app PUBLIC cxx_std_20)

target_include_directories(sample_app PUBLIC ${LLVM_BASE_DIR}/include)
target_link_directories(sample_app PUBLIC ${LLVM_BASE_DIR}/lib)

target_compile_definitions(sample_app PUBLIC ${LLVM_DEFINITIONS})

target_link_libraries(sample_app PRIVATE sample LLVM ${CLANG_LIBS})

add_executable(sample_test test/test.cpp)
target_compile_features(sample_test PUBLIC cxx_std_20)
target_link_libraries(sample_test PRIVATE Catch2::Catch2 sample spdlog::spdlog)

include(CTest)
include(Catch)
catch_discover_tests(sample_test)