#include <term.hpp>

#include <catch2/catch.hpp>

#include <sstream>

namespace {
auto to_string(const auto& printable) -> std::string
{
    std::ostringstream text;
    text << printable;
    return text.str();
}
}  // namespace

TEST_CASE("Greetings are printed correctly", "[greeting]")
{
    CHECK(to_string(term::greeting{}) == "Hello!");
    CHECK(to_string(term::greeting{"World"}) == "Hello World!");
    CHECK(to_string(term::greeting{"David"}) == "Hello David!");
}
