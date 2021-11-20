cmake_minimum_required(VERSION 3.20.3)

# Update submodules.
include(cmake/UpdateSubmodule.cmake)
option(GIT_SUBMODULE "Check submodules during build" ON)
update_submodule("${CMAKE_CURRENT_LIST_DIR}/vcpkg")

# Configure vcpkg (requires vcpkg submodule)
include(cmake/ConfigureVcpkg.cmake)
configure_vcpkg("${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(dh-term VERSION 0.0.1
                DESCRIPTION "dh::term library for vt100/xterm-style terminals "
                HOMEPAGE_URL https://github.com/dholmes215/term
                LANGUAGES CXX)

# Find dependencies.
find_package(Catch2 REQUIRED)
find_package(fmt 8.0.1 REQUIRED)

include(cmake/CompilerWarnings.cmake)

# Allow for static analysis options.
include(cmake/StaticAnalyzers.cmake)

add_subdirectory(src)

# Test the library.
include(CTest)
include(Catch)
add_subdirectory(tests)

# Create package configuration file.
include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dh-term-config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config.cmake"
                              INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dh-term)

# Create package version file.
set(version 0.0.1)

set_property(TARGET dh-term PROPERTY VERSION ${version})
# set_property(TARGET term PROPERTY SOVERSION 3)
set_property(TARGET dh-term PROPERTY
             INTERFACE_term_MAJOR_VERSION 0)
set_property(TARGET dh-term APPEND PROPERTY
             COMPATIBLE_INTERFACE_STRING term_MAJOR_VERSION)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config-version.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
)

# Install package configuration & version files.
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dh-term)
