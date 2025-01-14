#ifndef VECTOR_H
#define VECTOR_H

#include <cstring> 
#include <stdexcept> 
using namespace std;

template <typename T>
class Vector {
public:
    Vector() : size_(0), capacity_(10), data_(nullptr) {
        data_ = new T[capacity_];
    }

    ~Vector() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_] = value;
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    int size() const {
        return size_;
    }

    void clear() {
        size_ = 0;
    }

    bool empty() const {
        return size_ == 0;
    }

    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

private:
    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        memcpy(new_data, data_, sizeof(T) * size_);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

private:
    int size_;
    int capacity_;
    T* data_;
};

#endif 
