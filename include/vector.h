#pragma once

#include <iostream>
#include <algorithm> // для std::copy, std::move
#include <initializer_list>
#include <stdexcept> // для std::out_of_range

template <typename T>
class Vector {
private:
    T* data = nullptr;
    size_t capacity = 0;
    size_t size_ = 0;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vector() = default;

    explicit Vector(size_t count, const T& value = T()) {
        resize(count, value);
    }

    Vector(std::initializer_list<T> init) {
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
    }

    ~Vector() {
        delete[] data;
    }

    Vector(const Vector& other) {
        reserve(other.size_);
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector(Vector&& other) noexcept
        : data(other.data), size_(other.size_), capacity(other.capacity) {
        other.data = nullptr;
        other.size_ = 0;
        other.capacity = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            reserve(other.size_);
            size_ = other.size_;
            for (size_t i = 0; i < size_; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size_ = other.size_;
            capacity = other.capacity;
            other.data = nullptr;
            other.size_ = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Доступ к элементам
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& front() {
        return data[0];
    }

    const T& front() const {
        return data[0];
    }

    T& back() {
        return data[size_ - 1];
    }

    const T& back() const {
        return data[size_ - 1];
    }

    // Итераторы (упрощённые)
    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end() {
        return data + size_;
    }

    const T* end() const {
        return data + size_;
    }

    // Ёмкость
    bool empty() const {
        return size_ == 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            reallocate(new_capacity);
        }
    }

    void shrink_to_fit() {
        if (size_ < capacity) {
            reallocate(size_);
        }
    }

    // Модификаторы
    void clear() {
        size_ = 0;
    }

    void push_back(const T& value) {
        if (size_ >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        data[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        data[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity) {
            reserve(new_size);
        }
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                data[i] = value;
            }
        }
        size_ = new_size;
    }

    void get_blank() {
        for (int i = 0; i < size_; i++)
            resize(size_, T(0));
    }
};