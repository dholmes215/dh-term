#include "term.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

int main()
{
    fmt::print("{}\n", term::greeting{"World"});
}
