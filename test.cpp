#include "test.h"
#include <stdexcept>

int foo(int x) {
    if (x == 5) throw std::logic_error("x == 5");
    return x + 2;
}

int correct_foo(int x) {
    return x * 2;
}