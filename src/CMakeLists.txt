add_library(term term.cpp term.hpp)
target_include_directories(term INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(term PUBLIC project_options 
                           PRIVATE project_warnings fmt::fmt)

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE project_options project_warnings term fmt::fmt)
