#include <cstddef>
#ifndef INC_23_03_2026_VECTOR_TOP_IT_H
#define INC_23_03_2026_VECTOR_TOP_IT_H
namespace topit {
    template<class T>
    struct Vector {
        Vector();
        explicit Vector(size_t s, const T& val);
        ~Vector();

        Vector(const Vector<T> &) = delete;
        Vector<T> &operator=(const Vector<T> &) = delete;

        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;

        T& operator[](size_t id) noexcept;
        const T& operator[](size_t id) const noexcept;
        T& at(size_t id);
        const T& at(size_t id) const;

        private:
         T* data_;
         size_t size_;
         size_t capacity_;

    };
    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
}
template<class T>
topit::Vector<T>::Vector(size_t size, const T& val) :
data_(size ? new T[size] : nullptr),
size_(size),
capacity_(size)
{}
template<class T>
bool topit::Vector<T>::isEmpty() const noexcept {
    return !size_;
}
template<class T>
size_t topit::Vector<T>::getSize() const noexcept {
    return size_;
}
template<class T>
topit::Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}
template<class T>
topit::Vector<T>::~Vector() {
    delete[] data_;
template<class T>
T& topit::Vector<T>::at(size_t id) {
    return const_cast<T&>(static_cast<const Vector<T>&>(*this).at(id));
}
template<class T>
const T& topit::Vector<T>::at(size_t id) {
    if (id < getSize()) {
        return data_[id];
    }
    throw std::out_of_range("bad idea");
}
#endif