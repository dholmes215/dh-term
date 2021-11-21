set(term_SRC term.cpp)
set(term_INC term.hpp)

add_library(dh-term STATIC ${term_SRC} ${term_INC})
target_compile_features(dh-term PUBLIC cxx_std_20) # Require _at least_ C++20.
set_project_warnings(dh-term)
target_include_directories(dh-term INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(dh-term PRIVATE fmt::fmt)

add_executable(demo demo.cpp)
set_project_warnings(demo)
target_link_libraries(demo PRIVATE dh-term fmt::fmt)
