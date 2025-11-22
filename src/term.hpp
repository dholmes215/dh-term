//
// Copyright (c) 2021 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TERM_HPP
#define TERM_HPP

#include <fmt/format.h>

#include <algorithm>
#include <array>

namespace dh {

struct color final {
};

enum class sgr_code : uint8_t {
    reset = 0,
    bold = 1,
    faint = 2,
    italic = 3,
    underline = 4,
    slow_blink = 5,
    rapid_blink = 6,
    reverse_video = 7,
    conceal = 8,
    crossed_out = 9,
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37,
};

constexpr sgr_code lookup(const std::string_view name)
{
    constexpr std::array<std::string_view, 18> names{
        "reset",      "bold",        "faint",         "italic",  "underline",
        "slow_blink", "rapid_blink", "reverse_video", "conceal", "crossed_out",
        "black",      "red",         "green",         "yellow",  "blue",
        "magenta",    "cyan",        "white"};

    constexpr std::array sgrs{
        sgr_code::reset,       sgr_code::bold,          sgr_code::faint,
        sgr_code::italic,      sgr_code::underline,     sgr_code::slow_blink,
        sgr_code::rapid_blink, sgr_code::reverse_video, sgr_code::conceal,
        sgr_code::crossed_out, sgr_code::black,         sgr_code::red,
        sgr_code::green,       sgr_code::yellow,        sgr_code::blue,
        sgr_code::magenta,     sgr_code::cyan,          sgr_code::white};

    const auto found = std::ranges::find(names, name);
    if (found == names.end()) {
        throw "invalid sgr name";
    }
    return sgrs[static_cast<std::size_t>(std::distance(names.begin(), found))];
}

}  // namespace dh

// Custom formatter for dh::color
template <>
struct fmt::formatter<dh::color> {
    dh::sgr_code code{};

    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        auto it = ctx.begin();
        const auto end = std::ranges::find(ctx, '}');

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
    auto format(const dh::color /*unused*/, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "\x1B[{}m", static_cast<int>(code));
    }
};

#endif  // TERM_HPP
