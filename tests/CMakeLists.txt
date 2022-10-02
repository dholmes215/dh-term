add_executable(tests term_tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain fmt::fmt term)

catch_discover_tests(tests)
