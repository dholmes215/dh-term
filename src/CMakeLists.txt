set(term_SRC term.cpp)
set(term_INC term.hpp)

add_library(dh-term ${term_SRC} ${term_INC})
target_compile_features(dh-term PUBLIC cxx_std_20) # Require _at least_ C++20.
set_project_warnings(dh-term)
target_include_directories(dh-term INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(dh-term PRIVATE fmt::fmt)

add_executable(demo demo.cpp)
set_project_warnings(demo)
target_link_libraries(demo PRIVATE dh-term fmt::fmt)

# Install the library.
include(GNUInstallDirs)
if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_INSTALL_PREFIX "/opt/dholmes.us/${PROJECT_NAME}")
endif()

install(TARGETS dh-term
        EXPORT dh-term-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install public headers.
install(FILES ${term_INC} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install exported targets.
install(EXPORT dh-term-targets
        FILE dh-term-targets.cmake
        NAMESPACE dh::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dh-term)
