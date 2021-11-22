set(term_SRC term.cpp)
set(term_INC term.hpp)

add_library(term STATIC ${term_SRC} ${term_INC})
target_compile_features(term PUBLIC cxx_std_20) # Require _at least_ C++20.
target_include_directories(term INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(term PRIVATE fmt::fmt)

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE term fmt::fmt)

# Install the library.
include(GNUInstallDirs)

# if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
#     set(CMAKE_INSTALL_PREFIX "/opt/dholmes.us/${PROJECT_NAME}")
# endif()

install(TARGETS term
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
        DESTINATION ${CMAKE_INSTALL_DATADIR}/dh-term)
