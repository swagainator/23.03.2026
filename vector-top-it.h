#ifndef INC_23_03_2026_VECTOR_TOP_IT_H
#define INC_23_03_2026_VECTOR_TOP_IT_H

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace topit {
    template<class T>
    struct Vector {
        Vector();
        explicit Vector(size_t size);
        Vector(size_t size, const T& val);
        ~Vector();

        Vector(const Vector<T>& rhs);
        Vector<T>& operator=(Vector<T> rhs);
        Vector(Vector<T>&& rhs) noexcept;
        Vector<T>& operator=(Vector<T>&& rhs) noexcept;

        void swap(Vector<T>& rhs) noexcept;
        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;
        size_t getCapacity() const noexcept;


		// классная работа (copy & swap) + тесты
        void insert(size_t pos, const T& val);
        void insert(size_t pos, const Vector<T> &rhs, size_t b, size_t e);
        void erase(size_t pos);

        T& operator[](size_t id) noexcept;
        const T& operator[](size_t id) const noexcept;
        T& at(size_t id);
        const T& at(size_t id) const;
        void pushBack(const T& val);
        void pushFront(const T& val);

    private:
        T* data_;
        size_t size_;
        size_t capacity_;
    };

    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);

    template<class T>
    bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);


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
    Vector<T>::Vector(const Vector<T>& rhs)
        : data_(rhs.size_ ? new T[rhs.size_] : nullptr),
          size_(rhs.size_),
          capacity_(rhs.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = rhs.data_[i];
        }
    }

    template<class T>
    Vector<T>& Vector<T>::operator=(Vector<T> rhs) {
        swap(rhs);
        return *this;
    }

    template<class T>
    Vector<T>::Vector(Vector<T>&& rhs) noexcept
        : data_(rhs.data_), size_(rhs.size_), capacity_(rhs.capacity_) {
        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
    }

    template<class T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        Vector<T> tmp(std::move(rhs));
        swap(tmp);
        return *this;
    }

    template<class T>
    Vector<T>::~Vector() {
        delete[] data_;
    }

    template<class T>
    void Vector<T>::swap(Vector<T>& rhs) noexcept {
        using std::swap;
        swap(data_, rhs.data_);
        swap(size_, rhs.size_);
        swap(capacity_, rhs.capacity_);
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
    size_t Vector<T>::getCapacity() const noexcept {
        return capacity_;
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
    void Vector<T>::pushBack(const T& val) {
        if (size_ == capacity_) {
            const size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_] = val;
        ++size_;
    }
	template<class T>
	void topit::Vector<T>::pushFront(const T& val) {
        Vector<T> result(getSize() + 1);
        result[0] = val;
        for (size_t i = 0; i < getSize(); ++i) {
            result[i + 1] = (*this)[i];
		}
		swap(result);
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

    template<class T>
    bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(lhs == rhs);
    }

}

#endif

