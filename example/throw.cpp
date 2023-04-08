
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/context/fiber_context>

struct my_exception : public std::runtime_error {
    std::fiber_context    f;
    my_exception( std::fiber_context && f_, std::string const& what) :
        std::runtime_error{ what },
        f{ std::move( f_) } {
    }
};

int main() {
    std::fiber_context f{[](std::fiber_context && f) ->std::fiber_context {
        std::cout << "entered" << std::endl;
        try {
            f = std::move( f).resume();
        } catch ( my_exception & ex) {
            std::cerr << "my_exception: " << ex.what() << std::endl;
            return std::move( ex.f);
        }
        return {};
    }};
    f = std::move( f).resume();
    f = std::move( f).resume_with([](std::fiber_context && f) ->std::fiber_context {
        throw my_exception(std::move( f), "abc");
        return {};
    });

    std::cout << "main: done" << std::endl;

    return EXIT_SUCCESS;
}
