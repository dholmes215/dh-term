cmake_minimum_required(VERSION 3.20.3)

# Update submodules.
include(cmake/UpdateSubmodule.cmake)
option(GIT_SUBMODULE "Check submodules during build" OFF)
update_submodule("${CMAKE_CURRENT_LIST_DIR}/vcpkg")

# Configure vcpkg (requires vcpkg submodule)
include(cmake/ConfigureVcpkg.cmake)
configure_vcpkg("${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(dh-term VERSION 0.0.1
                DESCRIPTION "dh::term library for vt100/xterm-style terminals "
                HOMEPAGE_URL https://github.com/dholmes215/term
                LANGUAGES CXX)

# Disable testing by default.
option(BUILD_TESTING "Build the testing tree." OFF)

# Find dependencies.
find_package(fmt 8.0.1 REQUIRED)

include(cmake/CompilerWarnings.cmake)

# Allow for static analysis options.
include(cmake/StaticAnalyzers.cmake)

add_subdirectory(src)

if (BUILD_TESTING)
    # Test the library.
    find_package(Catch2 REQUIRED)
    include(CTest)
    include(Catch)
    add_subdirectory(tests)
endif()

# Create package configuration file.
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dh-term-config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config.cmake"
                              INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/dh-term
                              NO_SET_AND_CHECK_MACRO)

# Create package version file.

set_property(TARGET dh-term PROPERTY VERSION ${version})
# set_property(TARGET term PROPERTY SOVERSION 3)
set_property(TARGET dh-term PROPERTY
             INTERFACE_dh-term_MAJOR_VERSION 0)
set_property(TARGET dh-term APPEND PROPERTY
             COMPATIBLE_INTERFACE_STRING term_MAJOR_VERSION)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config-version.cmake"
    VERSION "${dh-term_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

# Install package configuration & version files.
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dh-term-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_DATADIR}/dh-term)

# Install the library.
# if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
#     set(CMAKE_INSTALL_PREFIX "/opt/dholmes.us/${PROJECT_NAME}")
# endif()

install(TARGETS dh-term
        EXPORT dh-term-targets)
        # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        # ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        # INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install public headers.
install(FILES ${term_INC} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install exported targets.
install(EXPORT dh-term-targets
        FILE dh-term-targets.cmake
        NAMESPACE dh::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/dh-term)
