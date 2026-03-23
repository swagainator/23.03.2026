#include "vector-top-it.h"
#include <iostream>
#include <cstddef>
bool test1() {
    using topit::Vector;

    Vector<int> v;
    return v.isEmpty();
}
int main() {
    using test_t = bool (*)();
    using case_t = std::pair<test_t, const char*>;
    case_t tests[] = {
        {test1, "Test 1: isEmpty() should return true for an empty vector."}
    };
    std::cout << std::boolalpha;
    for (size_t i = 0; i < sizeof(tests) / sizeof(case_t); ++i) {
        std::cout << tests[i].first()  << ":" << tests[i].second << "\n";
    }
}

