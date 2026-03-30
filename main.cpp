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

static bool test13_capacity_default() {
    const Vector<int> v;
    return v.getSize() == 0 && v.getCapacity() == 0;
}

static bool test14_capacity_constructed() {
    const Vector<int> v(5);
    return v.getSize() == 5 && v.getCapacity() == 5;
}

static bool test15_pushBack_single() {
    Vector<int> v;
    v.pushBack(10);
    return v.getSize() == 1 && v.getCapacity() >= 1 && v[0] == 10;
}

static bool test16_pushBack_growth_and_values() {
    Vector<int> v;
    const size_t cap0 = v.getCapacity();

    v.pushBack(1);
    const size_t cap1 = v.getCapacity();
    if (!(cap1 >= 1 && cap1 >= cap0)) {
        return false;
    }

    // Доводим до момента, когда точно понадобится рост
    while (v.getSize() < v.getCapacity()) {
        v.pushBack(7);
    }

    const size_t before = v.getCapacity();
    v.pushBack(99);
    const size_t after = v.getCapacity();

    if (!(after > before)) {
        return false;
    }
    if (v[v.getSize() - 1] != 99) {
        return false;
    }

    // Проверим, что старые значения не потерялись
    if (v[0] != 1) {
        return false;
    }

    return true;
}

static bool test17_equals_emptyVectors() {
    const Vector<int> a;
    const Vector<int> b;
    return (a == b) && !(a != b);
}

static bool test18_pushBack_preservesOrder() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);
    v.pushBack(5);

    if (v.getSize() != 5) {
        return false;
    }

    for (size_t i = 0; i < v.getSize(); ++i) {
        if (v[i] != static_cast<int>(i + 1)) {
            return false;
        }
    }

    return true;
}

static bool test19_pushBack_preservesAllElements_afterSeveralReallocations() {
    Vector<int> v;

    const int n = 100;
    for (int i = 0; i < n; ++i) {
        v.pushBack(i * 10);
    }

    if (v.getSize() != static_cast<size_t>(n)) {
        return false;
    }

    for (int i = 0; i < n; ++i) {
        if (v[static_cast<size_t>(i)] != i * 10) {
            return false;
        }
    }

    return true;
}

static bool test20_capacity_doubles_0_1_2_4_8() {
    Vector<int> v;
    if (v.getCapacity() != 0) {
        return false;
    }

    v.pushBack(1);
    if (v.getCapacity() != 1) {
        return false;
    }

    v.pushBack(2);
    if (v.getCapacity() != 2) {
        return false;
    }

    v.pushBack(3);
    if (v.getCapacity() != 4) {
        return false;
    }

    v.pushBack(4);
    if (v.getCapacity() != 4) {
        return false;
    }

    v.pushBack(5);
    if (v.getCapacity() != 8) {
        return false;
    }

    return true;
}

static bool test21_index_operator_nonConst_returnsReference() {
    Vector<int> v(3, 0);

    const size_t index = 1;
    int& ref = v[index];

    if (&ref != &v[index]) {
        return false;
    }

    ref = 123;
    return v[index] == 123;
}

static bool test22_equals_emptyAndNonEmpty() {
    const Vector<int> empty;
    const Vector<int> nonEmpty(1, 0);
    return (empty != nonEmpty) && !(empty == nonEmpty);
}

static bool test23_at_nonConst_returnsReference_addressCheck() {
    Vector<int> v(2, 5);
    int& r = v.at(0);
    if (&r != &v[0]) {
        return false;
    }
    r = 77;
    return v[0] == 77;
}
static bool test24_copyCtor_equal() {
    Vector<int> v(2, 0);
    Vector<int> yav = v;
    return yav == v;
}
static bool test25_copyAssign_equal() {
    Vector<int> v(2, 0);
    Vector<int> yav(v);
    bool res = v != yav;
    v = yav;
    return res && v == yav;
}
static bool test26_swap_swapsTwoVectors_andPreservesValues() {
    Vector<int> v(2, 0);
    Vector<int> yav(3,1);
    Vector<int> cpy_v(v);
    Vector<int> cpy_yav(yav);
    v.swap(yav);
    return v == cpy_yav && yav == cpy_v;
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
        {test13_capacity_default, "Test 13: getCapacity() == 0 for default vector"},
        {test14_capacity_constructed, "Test 14: getCapacity() equals size after Vector(n)"},
        {test15_pushBack_single, "Test 15: pushBack() adds one element"},
        {test16_pushBack_growth_and_values, "Test 16: pushBack() grows capacity and keeps values"},
        {test17_equals_emptyVectors, "Test 17: operator== true for two empty vectors"},
        {test18_pushBack_preservesOrder, "Test 18: pushBack() preserves element order"},
        {test19_pushBack_preservesAllElements_afterSeveralReallocations, "Test 19: pushBack() keeps all old elements after several reallocations"},
        {test20_capacity_doubles_0_1_2_4_8, "Test 20: capacity doubles 0->1->2->4->8 during pushBack()"},
        {test21_index_operator_nonConst_returnsReference, "Test 21: operator[] (non-const) is a true reference (address + write via ref)"},
        {test22_equals_emptyAndNonEmpty, "Test 22: operator== false and operator!= true for empty vs non-empty"},
        {test23_at_nonConst_returnsReference_addressCheck, "Test 23: at() (non-const) returns reference to element"},
        {test24_copyCtor_equal, "Test 24: Copy constructor creates equal vector"},
        {test25_copyAssign_equal, "Test 25: Assignment operator creates equal vector and does not break equality"},
        test26_swap_swapsTwoVectors_andPreservesValues, "Test 26: swap() swaps two vectors and preserves their values"
    }
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
