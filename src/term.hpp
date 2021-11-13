#ifndef TERM_HPP
#define TERM_HPP

#include <iostream>
#include <string>

namespace term {

struct greeting {
    std::string name{};
    friend auto operator<<(std::ostream& out, const greeting& obj)
        -> std::ostream&;
};

}  // namespace term

#endif  // TERM_HPP
