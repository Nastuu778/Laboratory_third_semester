#include "task.h"
#include <iostream>
#include <cassert>
#include <vector>

// Тестирование Vector
void test_vector()
{
    std::cout << "=== TESTING VECTOR ===" << std::endl;

    // 1. Создание контейнера
    Vector<int> vec;
    std::cout << "1. Container created" << std::endl;

    // 2. Добавление 10 элементов (0-9)
    std::cout << "2. Adding elements 0-9: ";
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    // 3. Вывод содержимого
    std::cout << "3. Container content: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата
    assert(vec.size() == 10);
    for (int i = 0; i < 10; ++i)
    {
        assert(vec[i] == i);
    }
    std::cout << "   Check passed: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9" << std::endl;

    // 4. Вывод размера
    std::cout << "4. Container size: " << vec.size() << std::endl;
    assert(vec.size() == 10);
    std::cout << "   Check passed: size = 10" << std::endl;

    // 5. Удаление третьего, пятого и седьмого элементов
    // Удаляем в обратном порядке, чтобы индексы не сдвигались
    vec.erase(6); // седьмой элемент (индекс 6)
    vec.erase(4); // пятый элемент (индекс 4)
    vec.erase(2); // третий элемент (индекс 2)
    std::cout << "5. Deleted 3rd, 5th and 7th elements" << std::endl;

    // 6. Вывод содержимого после удаления
    std::cout << "6. Content after deletion: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 0, 1, 3, 5, 7, 8, 9
    int expected_after_erase[] = {0, 1, 3, 5, 7, 8, 9};
    assert(vec.size() == 7);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        assert(vec[i] == expected_after_erase[i]);
    }
    std::cout << "   Check passed: 0, 1, 3, 5, 7, 8, 9" << std::endl;

    // 7. Добавление элемента 10 в начало
    vec.push_front(10);
    std::cout << "7. Added element 10 at the beginning" << std::endl;

    // 8. Вывод содержимого после добавления в начало
    std::cout << "8. Content after adding to beginning: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 5, 7, 8, 9
    int expected_after_front[] = {10, 0, 1, 3, 5, 7, 8, 9};
    assert(vec.size() == 8);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        assert(vec[i] == expected_after_front[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 5, 7, 8, 9" << std::endl;

    // 9. Добавление элемента 20 в середину
    size_t middle_index = vec.size() / 2;
    vec.insert(middle_index, 20);
    std::cout << "9. Added element 20 in the middle (position " << middle_index << ")" << std::endl;

    // 10. Вывод содержимого после добавления в середину
    std::cout << "10. Content after adding to middle: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 20, 5, 7, 8, 9
    int expected_after_middle[] = {10, 0, 1, 3, 20, 5, 7, 8, 9};
    assert(vec.size() == 9);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        assert(vec[i] == expected_after_middle[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 20, 5, 7, 8, 9" << std::endl;

    // 11. Добавление элемента 30 в конец
    vec.push_back(30);
    std::cout << "11. Added element 30 at the end" << std::endl;

    // 12. Вывод содержимого после добавления в конец
    std::cout << "12. Content after adding to end: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    int expected_final[] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    assert(vec.size() == 10);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        assert(vec[i] == expected_final[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30" << std::endl;

    std::cout << "=== ALL VECTOR TESTS PASSED SUCCESSFULLY ===\n"
              << std::endl;
}

// Тестирование DoublyLinkedList
void test_doubly_linked_list()
{
    std::cout << "=== TESTING DOUBLY LINKED LIST ===" << std::endl;

    // 1. Создание контейнера
    DoublyLinkedList<int> list;
    std::cout << "1. Container created" << std::endl;

    // 2. Добавление 10 элементов (0-9)
    std::cout << "2. Adding elements 0-9: ";
    for (int i = 0; i < 10; ++i)
    {
        list.push_back(i);
    }

    // 3. Вывод содержимого
    std::cout << "3. Container content: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата
    assert(list.size() == 10);
    for (int i = 0; i < 10; ++i)
    {
        assert(list[i] == i);
    }
    std::cout << "   Check passed: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9" << std::endl;

    // 4. Вывод размера
    std::cout << "4. Container size: " << list.size() << std::endl;
    assert(list.size() == 10);
    std::cout << "   Check passed: size = 10" << std::endl;

    // 5. Удаление третьего, пятого и седьмого элементов
    list.erase(6); // седьмой элемент
    list.erase(4); // пятый элемент
    list.erase(2); // третий элемент
    std::cout << "5. Deleted 3rd, 5th and 7th elements" << std::endl;

    // 6. Вывод содержимого после удаления
    std::cout << "6. Content after deletion: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 0, 1, 3, 5, 7, 8, 9
    int expected_after_erase[] = {0, 1, 3, 5, 7, 8, 9};
    assert(list.size() == 7);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_after_erase[i]);
    }
    std::cout << "   Check passed: 0, 1, 3, 5, 7, 8, 9" << std::endl;

    // 7. Добавление элемента 10 в начало
    list.push_front(10);
    std::cout << "7. Added element 10 at the beginning" << std::endl;

    // 8. Вывод содержимого после добавления в начало
    std::cout << "8. Content after adding to beginning: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 5, 7, 8, 9
    int expected_after_front[] = {10, 0, 1, 3, 5, 7, 8, 9};
    assert(list.size() == 8);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_after_front[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 5, 7, 8, 9" << std::endl;

    // 9. Добавление элемента 20 в середину
    size_t middle_index = list.size() / 2;
    list.insert(middle_index, 20);
    std::cout << "9. Added element 20 in the middle (position " << middle_index << ")" << std::endl;

    // 10. Вывод содержимого после добавления в середину
    std::cout << "10. Content after adding to middle: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 20, 5, 7, 8, 9
    int expected_after_middle[] = {10, 0, 1, 3, 20, 5, 7, 8, 9};
    assert(list.size() == 9);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_after_middle[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 20, 5, 7, 8, 9" << std::endl;

    // 11. Добавление элемента 30 в конец
    list.push_back(30);
    std::cout << "11. Added element 30 at the end" << std::endl;

    // 12. Вывод содержимого после добавления в конец
    std::cout << "12. Content after adding to end: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    int expected_final[] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    assert(list.size() == 10);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_final[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30" << std::endl;

    std::cout << "=== ALL DOUBLY LINKED LIST TESTS PASSED SUCCESSFULLY ===\n"
              << std::endl;
}

// Тестирование SinglyLinkedList
void test_singly_linked_list()
{
    std::cout << "=== TESTING SINGLY LINKED LIST ===" << std::endl;

    // 1. Создание контейнера
    SinglyLinkedList<int> list;
    std::cout << "1. Container created" << std::endl;

    // 2. Добавление 10 элементов (0-9)
    std::cout << "2. Adding elements 0-9: ";
    for (int i = 0; i < 10; ++i)
    {
        list.push_back(i);
    }

    // 3. Вывод содержимого
    std::cout << "3. Container content: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата
    assert(list.size() == 10);
    for (int i = 0; i < 10; ++i)
    {
        assert(list[i] == i);
    }
    std::cout << "   Check passed: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9" << std::endl;

    // 4. Вывод размера
    std::cout << "4. Container size: " << list.size() << std::endl;
    assert(list.size() == 10);
    std::cout << "   Check passed: size = 10" << std::endl;

    // 5. Удаление третьего, пятого и седьмого элементов
    list.erase(6); // седьмой элемент
    list.erase(4); // пятый элемент
    list.erase(2); // третий элемент
    std::cout << "5. Deleted 3rd, 5th and 7th elements" << std::endl;

    // 6. Вывод содержимого после удаления
    std::cout << "6. Content after deletion: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 0, 1, 3, 5, 7, 8, 9
    int expected_after_erase[] = {0, 1, 3, 5, 7, 8, 9};
    assert(list.size() == 7);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_after_erase[i]);
    }
    std::cout << "   Check passed: 0, 1, 3, 5, 7, 8, 9" << std::endl;

    // 7. Добавление элемента 10 в начало
    list.push_front(10);
    std::cout << "7. Added element 10 at the beginning" << std::endl;

    // 8. Вывод содержимого после добавления в начало
    std::cout << "8. Content after adding to beginning: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 5, 7, 8, 9
    int expected_after_front[] = {10, 0, 1, 3, 5, 7, 8, 9};
    assert(list.size() == 8);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_after_front[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 5, 7, 8, 9" << std::endl;

    // 9. Добавление элемента 20 в середину
    size_t middle_index = list.size() / 2;
    list.insert(middle_index, 20);
    std::cout << "9. Added element 20 in the middle (position " << middle_index << ")" << std::endl;

    // 10. Вывод содержимого после добавления в середину
    std::cout << "10. Content after adding to middle: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 20, 5, 7, 8, 9
    int expected_after_middle[] = {10, 0, 1, 3, 20, 5, 7, 8, 9};
    assert(list.size() == 9);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_after_middle[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 20, 5, 7, 8, 9" << std::endl;

    // 11. Добавление элемента 30 в конец
    list.push_back(30);
    std::cout << "11. Added element 30 at the end" << std::endl;

    // 12. Вывод содержимого после добавления в конец
    std::cout << "12. Content after adding to end: ";
    for (size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list[i];
        if (i < list.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;

    // Проверка ожидаемого результата: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    int expected_final[] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    assert(list.size() == 10);
    for (size_t i = 0; i < list.size(); ++i)
    {
        assert(list[i] == expected_final[i]);
    }
    std::cout << "   Check passed: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30" << std::endl;

    std::cout << "=== ALL SINGLY LINKED LIST TESTS PASSED SUCCESSFULLY ===\n"
              << std::endl;
}

// Дополнительные тесты для демонстрации возможностей
void demonstrate_additional_features()
{
    std::cout << "=== ADDITIONAL TESTS ===" << std::endl;

    // Тест семантики перемещения
    {
        Vector<int> v1;
        for (int i = 0; i < 5; ++i)
            v1.push_back(i * 10);

        Vector<int> v2 = std::move(v1);
        std::cout << "Move semantics Vector: ";
        for (size_t i = 0; i < v2.size(); ++i)
        {
            std::cout << v2[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Original vector after move (size): " << v1.size() << std::endl;
    }

    // Тест итераторов
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 3; ++i)
            list.push_back(i + 100);

        std::cout << "Iterators DoublyLinkedList: ";
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    // Тест емкости Vector
    {
        Vector<int> vec;
        std::cout << "Vector memory reservation:" << std::endl;
        for (int i = 0; i < 10; ++i)
        {
            vec.push_back(i);
            std::cout << "  size=" << vec.size() << ", capacity=" << vec.capacity();
            if (vec.capacity() > vec.size())
            {
                std::cout << " (has reserve)";
            }
            std::cout << std::endl;
        }
    }

    // Тест обратного итератора для двусвязного списка
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 3; ++i)
            list.push_back(i + 200);

        std::cout << "Reverse traversal DoublyLinkedList: ";
        auto it = list.end();
        --it; // переходим к последнему элементу
        for (; it != list.begin(); --it)
        {
            std::cout << *it << " ";
        }
        std::cout << *it << std::endl; // первый элемент
    }

    std::cout << std::endl;
}

int main()
{
    try
    {
        std::cout << "STARTING CONTAINER TESTS\n"
                  << std::endl;

        // Тестирование всех трёх контейнеров по отдельности
        test_vector();
        test_doubly_linked_list();
        test_singly_linked_list();

        // Дополнительные демонстрации
        demonstrate_additional_features();

        std::cout << "ALL TESTS PASSED SUCCESSFULLY!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "UNKNOWN ERROR" << std::endl;
        return 1;
    }

    return 0;
}