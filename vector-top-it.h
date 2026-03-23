#include <cstddef>
#ifndef INC_23_03_2026_VECTOR_TOP_IT_H
#define INC_23_03_2026_VECTOR_TOP_IT_H
namespace topit {
    template<class T>
    struct Vector {
        Vector();
        ~Vector();

        Vector(const Vector<T> &) = delete;
        Vector<T> &operator=(const Vector<T> &) = delete;

        bool isEmpty() const noexcept;

        private:
         T* data_;
         size_t size_;
         size_t capacity_;

    };
    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
}
template<class T>
bool topit::Vector<T>::isEmpty() const noexcept {
    return false;
}
template<class T>
topit::Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}
template<class T>
topit::Vector<T>::~Vector() {
    delete[] data_;
}
#endif