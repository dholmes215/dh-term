set(term_SRC term.cpp)
set(term_INC term.hpp)

add_library(term ${term_SRC} ${term_INC})
target_include_directories(term INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(term PUBLIC project_options 
                           PRIVATE project_warnings fmt::fmt)

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE project_options project_warnings term fmt::fmt)

# Install the library.
include(GNUInstallDirs)
if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_INSTALL_PREFIX "/opt/dholmes.us/${PROJECT_NAME}")
endif()

install(TARGETS term
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${term_INC} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
