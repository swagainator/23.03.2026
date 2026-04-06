#include "vector"

int main() {
    int a = 10;
    int b(a);
    struct A { int a;};
    A aa{10};
    int bb[] = {1, 2, 3,};
    std::vector<int> a{1, 2, 3, 4, 5};
    std::initializer_list<int> l{1, 2, 3, 4, 5};
}