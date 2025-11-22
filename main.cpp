#include <iostream>
#include <map>
#include "allocator.hpp"
#include "container.hpp"

int factorial(int n)
{
    if (n <= 1)
        return 1;
    int res = 1;
    for (int i = 2; i <= n; ++i)
    {
        res *= i;
    }
    return res;
}

int main()
{
    // 1) Создание экземпляра std::map<int, int>
    std::map<int, int> m1;

    // 2) Заполнение 10 элементами: ключ — 0..9, значение — факториал ключа
    for (int i = 0; i < 10; ++i)
    {
        m1[i] = factorial(i);
    }

    // Вывод m1 (обычный map)
    std::cout << "=== std::map (default allocator) ===\n";
    for (const auto &kv : m1)
    {
        std::cout << kv.first << " " << kv.second << "\n";
    }

    // 3) Создание std::map с кастомным аллокатором (лимит 10 элементов)
    using MyAlloc = chunk_allocator<std::pair<const int, int>>;
    std::map<int, int, std::less<int>, MyAlloc> m2(MyAlloc{10});

    // 4) Заполнение 10 элементами
    for (int i = 0; i < 10; ++i)
    {
        m2[i] = factorial(i);
    }

    // 5) Вывод m2
    std::cout << "=== std::map (custom allocator, limit=10) ===\n";
    for (const auto &kv : m2)
    {
        std::cout << kv.first << " " << kv.second << "\n";
    }

    // 6) Создание своего контейнера (без кастомного аллокатора)
    simple_container<int> cont1;

    // 7) Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i)
    {
        cont1.push_back(i);
    }

    // Вывод cont1
    std::cout << "=== simple_container (default allocator) ===\n";
    for (const auto &x : cont1)
    {
        std::cout << x << "\n";
    }

    // 8) Создание своего контейнера с кастомным аллокатором (лимит 10)
    simple_container<int, chunk_allocator<int>> cont2(chunk_allocator<int>{10});

    // 9) Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i)
    {
        cont2.push_back(i);
    }

    // Вывод cont2
    std::cout << "=== simple_container (custom allocator, limit=10) ===\n";
    for (const auto &x : cont2)
    {
        std::cout << x << "\n";
    }

    return 0;
}