//
// Copyright (c) 2021 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <term.hpp>

#include <fmt/core.h>
#include <fmt/format.h>
#include <catch2/catch_all.hpp>

TEST_CASE("Colors are printed correctly", "[color]")
{
    dh::color c;
    CHECK(fmt::format("{0:red}Hello {0:yellow}World{0:blue}!{0:reset}", c) ==
          "\x1B[31mHello \x1B[33mWorld\x1B[34m!\x1B[0m");
}
