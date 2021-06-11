cmake_minimum_required(VERSION 3.10)

project(cpp-project-template VERSION 0.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CMakePackageConfigHelpers)

find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(asio REQUIRED)
find_package(sdbus-c++ REQUIRED)

add_library(sample SHARED source/sample.cpp)
target_compile_features(sample PUBLIC cxx_std_20)
target_include_directories(sample 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sample>
    )
set_property(TARGET sample PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET sample PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/sampleConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(sampleConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/sampleConfig.cmake
    INSTALL_DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/sample/
)

install(TARGETS sample 
    EXPORT sampleTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT sampleTargets
    FILE
        sampleTargets.cmake
    NAMESPACE 
        "sample::"
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/sample/
    COMPONENT
        Devel
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/sampleConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/sampleConfigVersion.cmake"
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_ADS1256}
    COMPONENT
        Devel
)

install(FILES include/sample.h
    DESTINATION 
        ${CMAKE_INSTALL_INCLUDEDIR}/sample/
    COMPONENT 
        Devel
)

install(TARGETS sample DESTINATION ${CMAKE_INSTALL_LIBDIR})

add_executable(sample_client source/client/main.cpp)
target_compile_features(sample_client PUBLIC cxx_std_20)
target_link_libraries(sample_client PUBLIC SDBusCpp::sdbus-c++)

add_executable(sample_server source/server/main.cpp)
target_compile_features(sample_server PUBLIC cxx_std_20)
target_link_libraries(sample_server PRIVATE sample asio::asio SDBusCpp::sdbus-c++)

install(TARGETS sample_client sample_server DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(sample_test test/test.cpp)
target_compile_features(sample_test PUBLIC cxx_std_20)
target_link_libraries(sample_test PRIVATE Catch2::Catch2 sample spdlog::spdlog)

include(CTest)
include(Catch)
catch_discover_tests(sample_test)

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "Mikhail Tcukerman <michael@zuckerman.dev>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sample project")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_VENDOR})
set(CPACK_GENERATOR "RPM;DEB")

include(CPack)