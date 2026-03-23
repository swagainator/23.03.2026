#include "vector-top-it.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using topit::Vector;

static bool test1_isEmpty_empty() {
    Vector<int> v;
    return v.isEmpty();
}

static bool test2_getSize_empty() {
    Vector<int> v;
    return v.getSize() == 0;
}

static bool test3_getSize_nonEmpty() {
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    return v.getSize() == size;
}

static bool test4_at_nonConst_inRange() {
    constexpr size_t size = 3ull;
    Vector<int> v(size, 0);
    v.at(1) = 42;
    return v.at(1) == 42;
}

static bool test5_at_nonConst_outOfRange() {
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    try {
        (void)v.at(size);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

static bool test6_at_const_inRange() {
    constexpr size_t size = 2ull;
    const Vector<int> v(size, 7);
    return v.at(0) == 7 && v.at(1) == 7;
}

static bool test7_at_const_outOfRange() {
    constexpr size_t size = 3ull;
    const Vector<int> v(size);
    try {
        (void)v.at(size + 1);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

static bool test8_index_operator_nonConst() {
    Vector<int> v(3, 0);
    v[2] = 5;
    return v[2] == 5;
}

static bool test9_index_operator_const() {
    const Vector<int> v(3, 9);
    return v[0] == 9 && v[1] == 9 && v[2] == 9;
}

static bool test10_equals_and_notEquals_same() {
    const Vector<int> a(3, 1);
    const Vector<int> b(3, 1);
    return (a == b) && !(a != b);
}

static bool test11_notEquals_differentValue() {
    Vector<int> a(3, 1);
    Vector<int> b(3, 1);
    b[2] = 2;
    return (a != b) && !(a == b);
}

static bool test12_notEquals_differentSize() {
    const Vector<int> a(2, 1);
    const Vector<int> b(3, 1);
    return (a != b) && !(a == b);
}

int main() {
    using test_t = bool (*)();
    using case_t = std::pair<test_t, const char*>;

    case_t tests[] = {
        {test1_isEmpty_empty, "Test 1: isEmpty() returns true for empty vector"},
        {test2_getSize_empty, "Test 2: getSize() == 0 for empty vector"},
        {test3_getSize_nonEmpty, "Test 3: getSize() returns constructor size"},
        {test4_at_nonConst_inRange, "Test 4: at() (non-const) works in-range and allows write"},
        {test5_at_nonConst_outOfRange, "Test 5: at() (non-const) throws std::out_of_range when OOB"},
        {test6_at_const_inRange, "Test 6: at() (const) works in-range"},
        {test7_at_const_outOfRange, "Test 7: at() (const) throws std::out_of_range when OOB"},
        {test8_index_operator_nonConst, "Test 8: operator[] (non-const) returns reference"},
        {test9_index_operator_const, "Test 9: operator[] (const) returns const reference"},
        {test10_equals_and_notEquals_same, "Test 10: operator== true and operator!= false for equal vectors"},
        {test11_notEquals_differentValue, "Test 11: operator!= true for different values"},
        {test12_notEquals_differentSize, "Test 12: operator!= true for different sizes"},
    };

    std::cout << std::boolalpha;

    size_t successes = 0;
    size_t fails = 0;

    for (size_t i = 0; i < sizeof(tests) / sizeof(case_t); ++i) {
        const bool ok = tests[i].first();
        successes += ok ? 1 : 0;
        fails += ok ? 0 : 1;
        std::cout << ok << ": " << tests[i].second << std::endl;
    }

    std::cout << "Total: " << (sizeof(tests) / sizeof(case_t))
              << ", Successes: " << successes
              << ", Fails: " << fails << std::endl;

    return fails == 0 ? 0 : 1;
}
