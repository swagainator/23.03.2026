#ifndef INC_23_03_2026_VECTOR_TOP_IT_H
#define INC_23_03_2026_VECTOR_TOP_IT_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <initializer_list>
namespace topit {
    template<class T>
    struct Vector {
        struct iterator;
        struct const_iterator;

        Vector();
        explicit Vector(size_t size);
        Vector(size_t size, const T& val);
        ~Vector();

        Vector(std::initializer_list<T> il);
        Vector(const Vector<T>& rhs);
        Vector<T>& operator=(Vector<T> rhs);
        Vector(Vector<T>&& rhs) noexcept;
        Vector<T>& operator=(Vector<T>&& rhs) noexcept;

        void swap(Vector<T>& rhs) noexcept;
        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;
        size_t getCapacity() const noexcept;
        void reserve(size_t k);
        void shrinkToFit();
        void repeatPushBack(const T& val, size_t k);
        template<class IT>
            void rangedPushBack(IT b, IT e);


        void insert(size_t pos, const T& val);
        void insert(size_t pos, const Vector<T> &rhs, size_t b, size_t e);
        void erase(size_t pos);
        void insert(iterator pos, const T& val);
        void insert(iterator pos, const Vector<T>& rhs, const_iterator b, const_iterator e);
        void erase(iterator pos);

        T& operator[](size_t id) noexcept;
        const T& operator[](size_t id) const noexcept;
        T& at(size_t id);
        const T& at(size_t id) const;
        void pushBack(const T& val);
        void pushFront(const T& val);
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;

    private:
        T* data_;
        size_t size_;
        size_t capacity_;
    };

    template<class T>
    struct Vector<T>::iterator {
        T* ptr;

        iterator() : ptr(nullptr) {}
        explicit iterator(T* ptr) : ptr(ptr) {}

        T& operator*() const noexcept { return *ptr; }
        T* operator->() const noexcept { return ptr; }
        iterator& operator++() noexcept { ++ptr; return *this; }
        iterator operator++(int) noexcept { iterator tmp(*this); ++ptr; return tmp; }
        iterator& operator--() noexcept { --ptr; return *this; }
        iterator operator--(int) noexcept { iterator tmp(*this); --ptr; return tmp; }
        iterator operator+(size_t n) const noexcept { return iterator(ptr + n); }
        iterator operator-(size_t n) const noexcept { return iterator(ptr - n); }
        std::ptrdiff_t operator-(const iterator& rhs) const noexcept { return ptr - rhs.ptr; }
        bool operator==(const iterator& rhs) const noexcept { return ptr == rhs.ptr; }
        bool operator!=(const iterator& rhs) const noexcept { return ptr != rhs.ptr; }
        bool operator<(const iterator& rhs) const noexcept { return ptr < rhs.ptr; }
        bool operator<=(const iterator& rhs) const noexcept { return ptr <= rhs.ptr; }
        bool operator>(const iterator& rhs) const noexcept { return ptr > rhs.ptr; }
        bool operator>=(const iterator& rhs) const noexcept { return ptr >= rhs.ptr; }
    };

    template<class T>
    struct Vector<T>::const_iterator {
        const T* ptr;

        const_iterator() : ptr(nullptr) {}
        explicit const_iterator(const T* ptr) : ptr(ptr) {}
        const_iterator(const iterator& it) : ptr(it.ptr) {}

        const T& operator*() const noexcept { return *ptr; }
        const T* operator->() const noexcept { return ptr; }
        const_iterator& operator++() noexcept { ++ptr; return *this; }
        const_iterator operator++(int) noexcept { const_iterator tmp(*this); ++ptr; return tmp; }
        const_iterator& operator--() noexcept { --ptr; return *this; }
        const_iterator operator--(int) noexcept { const_iterator tmp(*this); --ptr; return tmp; }
        const_iterator operator+(size_t n) const noexcept { return const_iterator(ptr + n); }
        const_iterator operator-(size_t n) const noexcept { return const_iterator(ptr - n); }
        std::ptrdiff_t operator-(const const_iterator& rhs) const noexcept { return ptr - rhs.ptr; }
        bool operator==(const const_iterator& rhs) const noexcept { return ptr == rhs.ptr; }
        bool operator!=(const const_iterator& rhs) const noexcept { return ptr != rhs.ptr; }
        bool operator<(const const_iterator& rhs) const noexcept { return ptr < rhs.ptr; }
        bool operator<=(const const_iterator& rhs) const noexcept { return ptr <= rhs.ptr; }
        bool operator>(const const_iterator& rhs) const noexcept { return ptr > rhs.ptr; }
        bool operator>=(const const_iterator& rhs) const noexcept { return ptr >= rhs.ptr; }
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
    void Vector<T>::reserve(size_t k) {
        if (k <= capacity_) {
            return;
        }

        Vector<T> v;
        v.data_ = new T[k];
        v.size_ = size_;
        v.capacity_ = k;

        for (size_t i = 0; i < size_; ++i) {
            v.data_[i] = std::move(data_[i]);
        }
        swap(v);
    }

    template<class T>
    void Vector<T>::shrinkToFit() {
        if (size_ == capacity_) {
            return;
        }

        Vector<T> v;
        v.data_ = size_ ? new T[size_] : nullptr;
        v.size_ = size_;
        v.capacity_ = size_;

        for (size_t i = 0; i < size_; ++i) {
            v.data_[i] = std::move(data_[i]);
        }

        swap(v);
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
    topit::Vector<T>::Vector(std::initializer_list<T> il)
        : data_(il.size() ? new T[il.size()] : nullptr),
          size_(il.size()),
          capacity_(il.size()) {
        size_t i = 0;
        for (const T& val : il) {
            data_[i++] = val;
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
    typename Vector<T>::iterator Vector<T>::begin() noexcept {
        return iterator(data_);
    }

    template<class T>
    typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
        return const_iterator(data_);
    }

    template<class T>
    typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
        return const_iterator(data_);
    }

    template<class T>
    typename Vector<T>::iterator Vector<T>::end() noexcept {
        return iterator(data_ + size_);
    }

    template<class T>
    typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
        return const_iterator(data_ + size_);
    }

    template<class T>
    typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
        return const_iterator(data_ + size_);
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
    void topit::Vector<T>::repeatPushBack(const T& val, size_t k) {
        reserve(size_ + k);
        for (size_t i = 0; i < k; ++i) {
            data_[size_ + i] = val;
        }
        size_ += k;
    }

    template<class T>
    template<class IT>
    void topit::Vector<T>::rangedPushBack(IT b, IT e) {
        size_t count = 0;
        for (IT it = b; it != e; ++it) {
            ++count;
        }
        reserve(size_ + count);
        for (; b != e; ++b) {
            data_[size_] = *b;
            ++size_;
        }
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
    void Vector<T>::insert(size_t pos, const T& val) {
        if (pos > size_) {
            throw std::out_of_range("Vector::insert: pos out of range");
        }

        Vector<T> result(size_ + 1);

        for (size_t i = 0; i < pos; ++i) {
            result.data_[i] = data_[i];
        }

        result.data_[pos] = val;

        for (size_t i = pos; i < size_; ++i) {
            result.data_[i + 1] = data_[i];
        }

        swap(result);
    }

    template<class T>
    void Vector<T>::insert(size_t pos, const Vector<T>& rhs, size_t b, size_t e) {
        if (pos > size_) {
            throw std::out_of_range("Vector::insert: pos out of range");
        }
        if (b > e || e > rhs.size_) {
            throw std::out_of_range("Vector::insert: range out of range");
        }

        const size_t add = e - b;
        Vector<T> result(size_ + add);



        for (size_t i = 0; i < pos; ++i) {
            result.data_[i] = data_[i];
        }

        for (size_t i = 0; i < add; ++i) {
            result.data_[pos + i] = rhs.data_[b + i];
        }

        for (size_t i = pos; i < size_; ++i) {
            result.data_[add + i] = data_[i];
        }

        swap(result);
    }

    template<class T>
    void Vector<T>::insert(iterator pos, const T& val) {
        if (pos < begin() || pos > end()) {
            throw std::out_of_range("Vector::insert: iterator out of range");
        }
        insert(static_cast<size_t>(pos - begin()), val);
    }

    template<class T>
    void Vector<T>::insert(iterator pos, const Vector<T>& rhs, const_iterator b, const_iterator e) {
        if (pos < begin() || pos > end()) {
            throw std::out_of_range("Vector::insert: iterator out of range");
        }
        if (b < rhs.begin() || b > rhs.end() || e < rhs.begin() || e > rhs.end() || b > e) {
            throw std::out_of_range("Vector::insert: iterator range out of range");
        }
        insert(static_cast<size_t>(pos - begin()), rhs,
               static_cast<size_t>(b - rhs.begin()),
               static_cast<size_t>(e - rhs.begin()));
    }

    template<class T>
    void Vector<T>::erase(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Vector::erase: pos out of range");
        }

        Vector<T> result(size_ - 1);

        for (size_t i = 0; i < pos; ++i) {
            result.data_[i] = data_[i];
        }

        for (size_t i = pos + 1; i < size_; ++i) {
            result.data_[i - 1] = data_[i];
        }

        swap(result);
    }

    template<class T>
    void Vector<T>::erase(iterator pos) {
        if (pos < begin() || pos >= end()) {
            throw std::out_of_range("Vector::erase: iterator out of range");
        }
        erase(static_cast<size_t>(pos - begin()));
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

