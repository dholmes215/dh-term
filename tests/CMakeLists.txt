add_executable(tests tests.cpp term_tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 fmt::fmt term)

catch_discover_tests(tests)
