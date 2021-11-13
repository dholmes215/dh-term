//
// Copyright (c) 2021 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "term.hpp"

#include <map>
#include <string>
#include <string_view>

namespace dh {

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

sgr_code lookup(const std::string_view name)
{
    static const std::map<std::string_view, sgr_code> map{
        {"reset", sgr_code::reset},
        {"bold", sgr_code::bold},
        {"faint", sgr_code::faint},
        {"italic", sgr_code::italic},
        {"underline", sgr_code::underline},
        {"slow_blink", sgr_code::slow_blink},
        {"rapid_blink", sgr_code::rapid_blink},
        {"reverse_video", sgr_code::reverse_video},
        {"conceal", sgr_code::conceal},
        {"crossed_out", sgr_code::crossed_out},
        {"black", sgr_code::black},
        {"red", sgr_code::red},
        {"green", sgr_code::green},
        {"yellow", sgr_code::yellow},
        {"blue", sgr_code::blue},
        {"magenta", sgr_code::magenta},
        {"cyan", sgr_code::cyan},
        {"white", sgr_code::white},
    };
    return map.at(name);
}

}  // namespace dh
