add_executable(tests tests.cpp term_tests.cpp)
set_project_warnings(term)
target_link_libraries(tests PRIVATE Catch2::Catch2 fmt::fmt term)

catch_discover_tests(tests)
