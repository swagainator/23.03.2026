#ifndef INC_23_03_2026_VECTOR_TOP_IT_H
#define INC_23_03_2026_VECTOR_TOP_IT_H

#include <cstddef>
#include <stdexcept>

namespace topit {
    template<class T>
    struct Vector {
        Vector();
        explicit Vector(size_t size);
        Vector(size_t size, const T& val);
        ~Vector();

        Vector(const Vector<T>&) = delete;
        Vector<T>& operator=(const Vector<T>&) = delete;

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


    template<class T>
    Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

    template<class T>
    Vector<T>::Vector(size_t size)
        : data_(size ? new T[size] : nullptr), size_(size), capacity_(size) {}

    template<class T>
    Vector<T>::Vector(size_t size, const T& val)
        : data_(size ? new T[size] : nullptr), size_(size), capacity_(size) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = val;
        }
    }

    template<class T>
    Vector<T>::~Vector() {
        delete[] data_;
    }

    template<class T>
    bool Vector<T>::isEmpty() const noexcept {
        return size_ == 0;
    }

    template<class T>
    size_t Vector<T>::getSize() const noexcept {
        return size_;
    }

    template<class T>
    T& Vector<T>::operator[](size_t id) noexcept {
        return data_[id];
    }

    template<class T>
    const T& Vector<T>::operator[](size_t id) const noexcept {
        return data_[id];
    }

    template<class T>
    T& Vector<T>::at(size_t id) {
        return const_cast<T&>(static_cast<const Vector<T>&>(*this).at(id));
    }

    template<class T>
    const T& Vector<T>::at(size_t id) const {
        if (id < getSize()) {
            return data_[id];
        }
        throw std::out_of_range("Vector::at: index out of range");
    }

    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs.getSize() != rhs.getSize()) {
            return false;
        }
        for (size_t i = 0; i < lhs.getSize(); ++i) {
            if (!(lhs[i] == rhs[i])) {
                return false;
            }
        }
        return true;
    }
}

#endif

