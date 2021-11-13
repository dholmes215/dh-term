//
// Copyright (c) 2021 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TERM_HPP
#define TERM_HPP

#include <fmt/core.h>
#include <fmt/format.h>

#include <string>
#include <string_view>

namespace dh {

struct color final {
};

enum class sgr_code : uint8_t;

sgr_code lookup(const std::string_view name);

}  // namespace dh

// Custom formatter for aoc::solution_id
template <>
struct fmt::formatter<dh::color> {
    dh::sgr_code code{};

    /*constexpr*/ auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        auto it = ctx.begin();
        const auto end = std::find(ctx.begin(), ctx.end(), '}');

        // auto token_end = it;
        // while ((token_end = std::find(it, end, ',')) != end) {
        //     it = token_end;
        // }

        code = dh::lookup({it, end});

        // // Check if reached the end of the range:
        // if (it != end && *it != '}') {
        //     throw format_error("invalid format");
        // }
        return end;
    }

    template <typename FormatContext>
    auto format(const dh::color, FormatContext& ctx)
    {
        return format_to(ctx.out(), "\x1B[{}m", static_cast<int>(code));
    }
};

#endif  // TERM_HPP
