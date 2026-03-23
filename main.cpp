#include "vector-top-it.h"
#include <iostream>
#include <cstddef>
using topit::Vector;
bool test1() {


    Vector<int> v;
    return v.isEmpty();
}
bool test2() {


    Vector<int> v;
    return v.getSize() == 0;
}
bool test3() {
    constexpr size_t size = 3ull;

    Vector<int> v(size);
    return v.getSize() == 3;
}
bool test4() {
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    try {
        v.at(size);
        return true;
    } catch (...) {
        return false;
    }
}
bool test5() {
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    try {
        v.at(size+1);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

int main() {
    using test_t = bool (*)();
    using case_t = std::pair<test_t, const char*>;
    case_t tests[] = {
        {test1, "Test 1: isEmpty() should return true for an empty vector."},
        {test2, "Test 2: getSize() should return 0 for an empty vector."},
        {test3, "Test 3: getSize() should return the correct size for a non-empty vector."},
        {test4, "Test 4: at() should throw an exception when accessing out-of-bounds index."},
        {test5, "Test 5: at() should throw std::out_of_range when accessing out-of-bounds index."}
    };
    std::cout << std::boolalpha;
    for (size_t i = 0; i < sizeof(tests) / sizeof(case_t); ++i) {
        std::cout << tests[i].first()  << ":" << tests[i].second << "\n";
    }
}

