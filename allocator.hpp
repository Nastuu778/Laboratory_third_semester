#pragma once
#include <cstddef>
#include <new>
#include <vector>

template <typename T>
class chunk_allocator
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T *;

    // Дружба между всеми инстанциациями — обязательно для STL
    template <typename U>
    friend class chunk_allocator;

private:
    size_type chunk_size_;        // сколько элементов в одном блоке
    std::vector<T *> blocks_;     // все выделенные блоки (для освобождения в деструкторе)
    std::vector<T *> free_slots_; // ранее освобождённые слоты (для повторного использования)

public:
    explicit chunk_allocator(size_type chunk_size = 10)
        : chunk_size_(chunk_size ? chunk_size : 10) {}

    // Конструктор от другого типа — для rebind
    template <typename U>
    chunk_allocator(const chunk_allocator<U> &other)
        : chunk_size_(other.chunk_size_) {}

    ~chunk_allocator()
    {
        // Освобождаем все блоки
        for (T *block : blocks_)
        {
            ::operator delete(block);
        }
    }

    T *allocate(size_type n)
    {
        if (n == 0)
            return nullptr;

        // STL-контейнеры (включая std::map) всегда вызывают allocate(1)
        if (n == 1)
        {
            // Сначала пробуем использовать свободный слот
            if (!free_slots_.empty())
            {
                T *ptr = free_slots_.back();
                free_slots_.pop_back();
                return ptr;
            }

            // Если свободных слотов нет — выделяем новый блок
            T *new_block = static_cast<T *>(::operator new(chunk_size_ * sizeof(T)));
            blocks_.push_back(new_block);

            // Все слоты, кроме первого, добавляем в free_slots_
            for (size_type i = 1; i < chunk_size_; ++i)
            {
                free_slots_.push_back(new_block + i);
            }

            return new_block; // первый слот отдаём сразу
        }

        // Для n > 1 (редко, но может быть) — выделяем отдельно
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }

    void deallocate(T *p, size_type n) noexcept
    {
        if (n == 1)
        {
            // Возвращаем слот в пул
            free_slots_.push_back(p);
        }
        else
        {
            // Освобождаем "сырой" блок
            ::operator delete(p);
        }
    }

    // rebind — обязательно для совместимости с STL
    template <typename U>
    struct rebind
    {
        using other = chunk_allocator<U>;
    };
};

// Обязательные операторы сравнения
template <typename T, typename U>
bool operator==(const chunk_allocator<T> &, const chunk_allocator<U> &)
{
    return true;
}

template <typename T, typename U>
bool operator!=(const chunk_allocator<T> &a, const chunk_allocator<U> &b)
{
    return !(a == b);
}