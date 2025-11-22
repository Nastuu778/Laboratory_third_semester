#pragma once
#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <memory> // для std::allocator

template <typename T, typename Allocator = std::allocator<T>>
class simple_container
{
public:
    using value_type = T;                                               // что хранится
    using allocator_type = Allocator;                                   // какой аллокатор используется
    using size_type = std::size_t;                                      // тип для размеров
    using pointer = typename std::allocator_traits<Allocator>::pointer; // тип указателя, полученный через allocator_traits

private:
    Allocator alloc_;        // экземпляр аллокатора
    T *data_ = nullptr;      // указатель на начало выделенного блока памяти
    size_type size_ = 0;     // сколько элементов реально хранится
    size_type capacity_ = 0; // сколько элементов помещается в текущем блоке

    // Увеличить ёмкость (как vector)
    void grow()
    {
        size_type new_cap = (capacity_ == 0) ? 1 : capacity_ * 2; // если вместимость=0 выделяем блок на 1 элемент
        T *new_data = alloc_.allocate(new_cap);                   // вызывает аллокатор, чтобы получить сырой блок памяти

        // Переместить старые элементы
        for (size_type i = 0; i < size_; ++i) // size_ — сколько объектов действительно создано
        {
            new (new_data + i) T(std::move(data_[i]));
            (data_ + i)->~T(); // явный вызов деструктора
        }

        if (data_) // data_ — указатель на старый блок памяти
        {
            alloc_.deallocate(data_, capacity_); // capacity_ — сколько поместится
        }

        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    // Конструктор по умолчанию
    simple_container() = default;

    // Конструктор с аллокатором
    explicit simple_container(const Allocator &alloc) : alloc_(alloc) {}
    // explicit чтобы конструктор нельзя было использовать случайно
    //  Деструктор
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

    void push_back(const T &value) // добавляет копию переданного объекта в конец
    {
        if (size_ >= capacity_) // Проверяет хватает ли места в текущем блоке памяти
        {
            grow(); // чтобы разширить блок
        }
        new (data_ + size_) T(value); // data_ + size_ — адрес первой свободной ячейки в блоке
        // T(value) — вызывает копирующий конструктор
        ++size_;
    }

    size_type size() const { return size_; }  // Возвращает текущее количество элементов в контейнере
    bool empty() const { return size_ == 0; } // Проверяет, пуст ли контейнер.

    // Итератор
    T *begin() { return data_; }
    T *end() { return data_ + size_; }
    const T *begin() const { return data_; }
    const T *end() const { return data_ + size_; }
};