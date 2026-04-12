#include "vector-top-it.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using topit::Vector;

bool test1_isEmpty_empty() {
    Vector<int> v;
    return v.isEmpty();
}

bool test2_getSize_empty() {
    Vector<int> v;
    return v.getSize() == 0;
}

bool test3_getSize_nonEmpty() {
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    return v.getSize() == size;
}

bool test4_at_nonConst_inRange() {
    constexpr size_t size = 3ull;
    Vector<int> v(size, 0);
    v.at(1) = 42;
    return v.at(1) == 42;
}

bool test5_at_nonConst_outOfRange() {
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

bool test6_at_const_inRange() {
    constexpr size_t size = 2ull;
    const Vector<int> v(size, 7);
    return v.at(0) == 7 && v.at(1) == 7;
}

bool test7_at_const_outOfRange() {
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

bool test8_index_operator_nonConst() {
    Vector<int> v(3, 0);
    v[2] = 5;
    return v[2] == 5;
}

bool test9_index_operator_const() {
    const Vector<int> v(3, 9);
    return v[0] == 9 && v[1] == 9 && v[2] == 9;
}

bool test10_equals_and_notEquals_same() {
    const Vector<int> a(3, 1);
    const Vector<int> b(3, 1);
    return (a == b) && !(a != b);
}

bool test11_notEquals_differentValue() {
    Vector<int> a(3, 1);
    Vector<int> b(3, 1);
    b[2] = 2;
    return (a != b) && !(a == b);
}

bool test12_notEquals_differentSize() {
    const Vector<int> a(2, 1);
    const Vector<int> b(3, 1);
    return (a != b) && !(a == b);
}

bool test13_capacity_default() {
    const Vector<int> v;
    return v.getSize() == 0 && v.getCapacity() == 0;
}

bool test14_capacity_constructed() {
    const Vector<int> v(5);
    return v.getSize() == 5 && v.getCapacity() == 5;
}

bool test15_pushBack_single() {
    Vector<int> v;
    v.pushBack(10);
    return v.getSize() == 1 && v.getCapacity() >= 1 && v[0] == 10;
}

bool test16_pushBack_growth_and_values() {
    Vector<int> v;
    const size_t cap0 = v.getCapacity();

    v.pushBack(1);
    const size_t cap1 = v.getCapacity();
    if (!(cap1 >= 1 && cap1 >= cap0)) {
        return false;
    }

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

bool test17_equals_emptyVectors() {
    const Vector<int> a;
    const Vector<int> b;
    return (a == b) && !(a != b);
}

bool test18_pushBack_preservesOrder() {
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

bool test19_pushBack_preservesAllElements_afterSeveralReallocations() {
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

bool test20_capacity_doubles_0_1_2_4_8() {
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

bool test21_index_operator_nonConst_returnsReference() {
    Vector<int> v(3, 0);

    const size_t index = 1;
    int& ref = v[index];

    if (&ref != &v[index]) {
        return false;
    }

    ref = 123;
    return v[index] == 123;
}

bool test22_equals_emptyAndNonEmpty() {
    const Vector<int> empty;
    const Vector<int> nonEmpty(1, 0);
    return (empty != nonEmpty) && !(empty == nonEmpty);
}

bool test23_at_nonConst_returnsReference_addressCheck() {
    Vector<int> v(2, 5);
    int& r = v.at(0);
    if (&r != &v[0]) {
        return false;
    }
    r = 77;
    return v[0] == 77;
}

bool test24_copyCtor_equal() {
    Vector<int> v(2, 0);
    Vector<int> yav = v;
    return yav == v;
}

bool test25_copyAssign_equal() {
    Vector<int> v(2, 0);
    Vector<int> yav(v);
    const bool res = (v == yav);
    v = yav;
    return res && v == yav;
}

bool test26_swap_swapsTwoVectors_andPreservesValues() {
    Vector<int> v(2, 0);
    Vector<int> yav(3, 1);
    Vector<int> cpy_v(v);
    Vector<int> cpy_yav(yav);
    v.swap(yav);
    return v == cpy_yav && yav == cpy_v;
}

bool test27_insert_single_begin() {
    Vector<int> v(3, 7);
    v.insert(0, 1);
    return v.getSize() == 4 && v[0] == 1 && v[1] == 7 && v[2] == 7 && v[3] == 7;
}

bool test28_insert_single_middle_end() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(4);

    v.insert(2, 3);
    if (!(v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4)) {
        return false;
    }

    v.insert(v.getSize(), 5);
    return v.getSize() == 5 && v[4] == 5;
}

bool test29_insert_range() {
    Vector<int> a;
    a.pushBack(1);
    a.pushBack(4);

    Vector<int> b;
    b.pushBack(9);
    b.pushBack(8);
    b.pushBack(7);
    b.pushBack(6);

    a.insert(1, b, 1, 3);

    return a.getSize() == 4 && a[0] == 1 && a[1] == 8 && a[2] == 7 && a[3] == 4;
}

bool test30_erase_middle() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);

    v.erase(1);
    return v.getSize() == 3 && v[0] == 1 && v[1] == 3 && v[2] == 4;
}

bool test31_insert_erase_outOfRange_throws() {
    Vector<int> v(1, 0);

    try {
        v.insert(2, 1);
        return false;
    } catch (const std::out_of_range&) {
    } catch (...) {
        return false;
    }

    try {
        v.erase(1);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool test32_insert_iterator_begin() {
    Vector<int> v;
    v.pushBack(2);
    v.pushBack(3);

    v.insert(v.begin(), 1);

    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool test33_insert_iterator_middle() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(3);
    v.pushBack(4);

    v.insert(v.begin() + 1, 2);

    return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;
}

bool test34_insert_iterator_range() {
    Vector<int> a;
    a.pushBack(1);
    a.pushBack(5);

    Vector<int> b;
    b.pushBack(2);
    b.pushBack(3);
    b.pushBack(4);
    b.pushBack(9);

    a.insert(a.begin() + 1, b, b.begin(), b.begin() + 3);

    return a.getSize() == 5 && a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5;
}

bool test35_erase_iterator_begin() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);

    v.erase(v.begin());

    return v.getSize() == 2 && v[0] == 2 && v[1] == 3;
}

bool test36_erase_iterator_middle() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);

    v.erase(v.begin() + 2);

    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 4;
}

bool test37_erase_iterator_end_minus_one() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);

    v.erase(v.end() - 1);

    return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool test38_initializerList_constructsAndIndexes() {
    Vector<int> v{3, 1};
    return (v.getSize() == 2) && (v.at(0) == 3) && (v[1] == 1);
}

bool test39_initializerList_empty_isEmpty() {
    Vector<int> v{};
    return v.isEmpty();
}

bool test40_reserve_increasesCapacity_butKeepsSizeAndValues() {
    Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    v.reserve(10);

    return v.getSize() == 3 && v.getCapacity() == 10
           && v[0] == 10 && v[1] == 20 && v[2] == 30;
}

bool test41_shrinkToFit_reducesCapacityToSize() {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);
    v.erase(1);

    const size_t size_before = v.getSize();
    v.shrinkToFit();

    return v.getSize() == size_before && v.getCapacity() == size_before
           && v[0] == 1 && v[1] == 3 && v[2] == 4;
}

bool test42_repeatPushBack_appendsSeveralEqualValues() {
    Vector<int> v;
    v.pushBack(5);

    v.repeatPushBack(7, 3);

    return v.getSize() == 4
           && v[0] == 5 && v[1] == 7 && v[2] == 7 && v[3] == 7;
}

bool test43_rangedPushBack_appendsWholeRange() {
    Vector<int> source;
    source.pushBack(2);
    source.pushBack(4);
    source.pushBack(6);

    Vector<int> v;
    v.pushBack(1);
    v.rangedPushBack(source.begin(), source.end());

    return v.getSize() == 4
           && v[0] == 1 && v[1] == 2 && v[2] == 4 && v[3] == 6;
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
        {test26_swap_swapsTwoVectors_andPreservesValues, "Test 26: swap() swaps two vectors and preserves their values"},
        {test27_insert_single_begin, "Test 27: insert(pos,val) inserts at begin"},
        {test28_insert_single_middle_end, "Test 28: insert(pos,val) inserts in middle and end"},
        {test29_insert_range, "Test 29: insert(pos, rhs, b, e) inserts a range"},
        {test30_erase_middle, "Test 30: erase(pos) removes element"},
        {test31_insert_erase_outOfRange_throws, "Test 31: insert/erase throw std::out_of_range for invalid pos"},
        {test32_insert_iterator_begin, "Test 32: insert(it, val) inserts at begin iterator"},
        {test33_insert_iterator_middle, "Test 33: insert(it, val) inserts at middle iterator"},
        {test34_insert_iterator_range, "Test 34: insert(it, rhs, b, e) inserts iterator range"},
        {test35_erase_iterator_begin, "Test 35: erase(it) removes first element"},
        {test36_erase_iterator_middle, "Test 36: erase(it) removes middle element"},
        {test37_erase_iterator_end_minus_one, "Test 37: erase(end()-1) removes last element"},
        {test38_initializerList_constructsAndIndexes, "Test 38: initializer_list constructs vector and indexing works"},
        {test39_initializerList_empty_isEmpty, "Test 39: initializer_list empty {} creates empty vector"},
        {test40_reserve_increasesCapacity_butKeepsSizeAndValues, "Test 40: reserve() increases capacity and keeps size and values"},
        {test41_shrinkToFit_reducesCapacityToSize, "Test 41: shrinkToFit() reduces capacity to current size"},
        {test42_repeatPushBack_appendsSeveralEqualValues, "Test 42: repeatPushBack() appends k copies of value"},
        {test43_rangedPushBack_appendsWholeRange, "Test 43: rangedPushBack() appends elements from iterator range"},
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
