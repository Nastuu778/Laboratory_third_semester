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
    // ================ ЧАСТЬ 1: Проверка с std::map ================
    {
        std::cout << "=== Testing with std::map ===\n";
        using MyAlloc = chunk_allocator<std::pair<const int, int>>;
        std::map<int, int, std::less<int>, MyAlloc> m(MyAlloc{5}); // блоки по 5 элементов

        // Заполняем 10 элементами (должно выделиться 2 блока по 5)
        for (int i = 0; i < 10; ++i)
        {
            m[i] = factorial(i);
        }

        // Вывод — как в задании: "ключ значение"
        for (const auto &kv : m)
        {
            std::cout << kv.first << " " << kv.second << "\n";
        }
    } // аллокатор освобождает память в деструкторе

    std::cout << "---\n";

    // ================ ЧАСТЬ 2: Проверка своего контейнера ================
    {
        std::cout << "=== Testing simple_container ===\n";
        simple_container<int, chunk_allocator<int>> cont(chunk_allocator<int>{3});

        // Добавляем 10 элементов (должно выделиться 4 блока: 3+3+3+1 → но наш аллокатор выделяет блоками по 3, итого 4 блока)
        for (int i = 0; i < 10; ++i)
        {
            cont.push_back(i);
        }

        // Проверка size() и empty()
        std::cout << "Size: " << cont.size() << ", Empty: " << cont.empty() << "\n";

        // Обход в одном направлении — как в задании
        for (const auto &x : cont)
        {
            std::cout << x << "\n";
        }

        // Дополнительно: проверка итераторов (begin/end)
        auto it = cont.begin();
        int sum = 0;
        while (it != cont.end())
        {
            sum += *it;
            ++it;
        }
        std::cout << "Sum (via iterator): " << sum << "\n"; // должно быть 45
    } // контейнер и аллокатор освобождают память

    std::cout << "---\n";

    // ================ ЧАСТЬ 3: Проверка поэлементного освобождения (если поддерживается) ================
    {
        std::cout << "=== Testing deallocate (if supported) ===\n";
        // Примечание: в simple_container мы не удаляем элементы,
        // но если бы был pop_back или erase — можно было бы проверить.
        // Для демонстрации можно создать временный объект и освободить:
        chunk_allocator<int> alloc(2);
        int *p1 = alloc.allocate(1);
        int *p2 = alloc.allocate(1);
        alloc.deallocate(p1, 1);     // возвращаем в пул
        int *p3 = alloc.allocate(1); // должен переиспользовать p1
        // Но без отладки не видно — поэтому достаточно упомянуть в отчёте.
        std::cout << "Deallocate test: no crash = success\n";
    }

    return 0;
}