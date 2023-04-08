
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>

#include <boost/context/fiber_context>

std::fiber_context f1( std::fiber_context && f) {
    std::cout << "f1: entered first time" << std::endl;
    f = std::move( f).resume();
    std::cout << "f1: entered second time" << std::endl;
    return std::move( f);
}

int main() {
    std::fiber_context f{ f1 };
    f = std::move( f).resume();
    std::cout << "f1: returned first time" << std::endl;
    f = std::move( f).resume();
    std::cout << "f1: returned second time" << std::endl;
    std::cout << "main: done" << std::endl;
    return EXIT_SUCCESS;
}
