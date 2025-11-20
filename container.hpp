#pragma once
#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <memory> // для std::allocator

template <typename T, typename Allocator = std::allocator<T>>
class simple_container
{
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;

private:
    Allocator alloc_;
    T *data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;

    // Увеличить ёмкость (как vector)
    void grow()
    {
        size_type new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
        T *new_data = alloc_.allocate(new_cap);

        // Переместить старые элементы
        for (size_type i = 0; i < size_; ++i)
        {
            new (new_data + i) T(std::move(data_[i]));
            (data_ + i)->~T();
        }

        if (data_)
        {
            alloc_.deallocate(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    // Конструктор по умолчанию
    simple_container() = default;

    // Конструктор с аллокатором
    explicit simple_container(const Allocator &alloc) : alloc_(alloc) {}

    // Деструктор
    ~simple_container()
    {
        for (size_type i = 0; i < size_; ++i)
        {
            (data_ + i)->~T();
        }
        if (data_)
        {
            alloc_.deallocate(data_, capacity_);
        }
    }

    void push_back(const T &value)
    {
        if (size_ >= capacity_)
        {
            grow();
        }
        new (data_ + size_) T(value);
        ++size_;
    }

    size_type size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Итератор (очень простой)
    T *begin() { return data_; }
    T *end() { return data_ + size_; }
    const T *begin() const { return data_; }
    const T *end() const { return data_ + size_; }
};