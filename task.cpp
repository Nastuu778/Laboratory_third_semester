#include "task.h"
#include <iostream>
#include <utility>

// ==================== РЕАЛИЗАЦИИ ВСПОМОГАТЕЛЬНЫХ СТРУКТУР ====================

template <typename T>
DoublyListNode<T>::DoublyListNode(const T &value)
    : data(value), next(nullptr), prev(nullptr) {}

template <typename T>
DoublyListNode<T>::DoublyListNode(T &&value)
    : data(std::move(value)), next(nullptr), prev(nullptr) {}

template <typename T>
SinglyListNode<T>::SinglyListNode(const T &value)
    : data(value), next(nullptr) {}

template <typename T>
SinglyListNode<T>::SinglyListNode(T &&value)
    : data(std::move(value)), next(nullptr) {}

// ==================== РЕАЛИЗАЦИИ ИТЕРАТОРОВ ====================

template <typename T, typename NodeT>
BaseIterator<T, NodeT>::BaseIterator(NodeT *node) : current(node) {}

template <typename T, typename NodeT>
T &BaseIterator<T, NodeT>::operator*() const { return current->data; }

template <typename T, typename NodeT>
T *BaseIterator<T, NodeT>::operator->() const { return &current->data; }

template <typename T, typename NodeT>
BaseIterator<T, NodeT> &BaseIterator<T, NodeT>::operator++()
{
    if (current)
        current = current->next.get();
    return *this;
}

template <typename T, typename NodeT>
BaseIterator<T, NodeT> BaseIterator<T, NodeT>::operator++(int)
{
    BaseIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T, typename NodeT>
bool BaseIterator<T, NodeT>::operator==(const BaseIterator &other) const
{
    return current == other.current;
}

template <typename T, typename NodeT>
bool BaseIterator<T, NodeT>::operator!=(const BaseIterator &other) const
{
    return current != other.current;
}

template <typename T>
DoublyListIterator<T> &DoublyListIterator<T>::operator--()
{
    if (this->current)
        this->current = this->current->prev;
    return *this;
}

template <typename T>
DoublyListIterator<T> DoublyListIterator<T>::operator--(int)
{
    DoublyListIterator temp = *this;
    --(*this);
    return temp;
}

// ==================== РЕАЛИЗАЦИИ VECTOR ====================

template <typename T>
Vector<T>::Vector() : data(nullptr), capacity_(0), size_(0) {}

template <typename T>
Vector<T>::Vector(const Vector &other) : capacity_(other.capacity_), size_(other.size_)
{
    data = std::make_unique<T[]>(capacity_);
    for (size_t i = 0; i < size_; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector &&other) noexcept
    : data(std::move(other.data)), capacity_(other.capacity_), size_(other.size_)
{
    other.capacity_ = 0;
    other.size_ = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &other)
{
    if (this != &other)
    {
        auto new_data = std::make_unique<T[]>(other.capacity_);
        for (size_t i = 0; i < other.size_; ++i)
        {
            new_data[i] = other.data[i];
        }
        data = std::move(new_data);
        capacity_ = other.capacity_;
        size_ = other.size_;
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    if (size_ == capacity_)
    {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    data[size_++] = value;
}

template <typename T>
void Vector<T>::push_back(T &&value)
{
    if (size_ == capacity_)
    {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    data[size_++] = std::move(value);
}

template <typename T>
void Vector<T>::insert(size_t index, const T &value)
{
    if (index > size_)
        throw std::out_of_range("Index out of range");

    if (size_ == capacity_)
    {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }

    for (size_t i = size_; i > index; --i)
    {
        data[i] = std::move(data[i - 1]);
    }
    data[index] = value;
    ++size_;
}

template <typename T>
void Vector<T>::insert(size_t index, T &&value)
{
    if (index > size_)
        throw std::out_of_range("Index out of range");

    if (size_ == capacity_)
    {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }

    for (size_t i = size_; i > index; --i)
    {
        data[i] = std::move(data[i - 1]);
    }
    data[index] = std::move(value);
    ++size_;
}

template <typename T>
void Vector<T>::erase(size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    for (size_t i = index; i < size_ - 1; ++i)
    {
        data[i] = std::move(data[i + 1]);
    }
    --size_;
}

template <typename T>
T &Vector<T>::operator[](size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
const T &Vector<T>::operator[](size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
size_t Vector<T>::size() const { return size_; }

template <typename T>
size_t Vector<T>::capacity() const { return capacity_; }

template <typename T>
T *Vector<T>::begin() { return data.get(); }

template <typename T>
T *Vector<T>::end() { return data.get() + size_; }

template <typename T>
const T *Vector<T>::begin() const { return data.get(); }

template <typename T>
const T *Vector<T>::end() const { return data.get() + size_; }

template <typename T>
void Vector<T>::push_front(const T &value)
{
    insert(0, value);
}

template <typename T>
void Vector<T>::push_front(T &&value)
{
    insert(0, std::move(value));
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity)
{
    auto new_data = std::make_unique<T[]>(new_capacity);
    for (size_t i = 0; i < size_; ++i)
    {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
    capacity_ = new_capacity;
}

// ==================== РЕАЛИЗАЦИИ DOUBLY LINKED LIST ====================

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList &&other) noexcept
    : head(std::move(other.head)), tail(other.tail), size_(other.size_)
{
    other.tail = nullptr;
    other.size_ = 0;
}

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(DoublyLinkedList &&other) noexcept
{
    if (this != &other)
    {
        head = std::move(other.head);
        tail = other.tail;
        size_ = other.size_;
        other.tail = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T &value)
{
    auto newNode = std::make_unique<DoublyListNode<T>>(value);
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++size_;
}

template <typename T>
void DoublyLinkedList<T>::push_back(T &&value)
{
    auto newNode = std::make_unique<DoublyListNode<T>>(std::move(value));
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++size_;
}

template <typename T>
void DoublyLinkedList<T>::insert(size_t index, const T &value)
{
    if (index > size_)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        push_front(value);
        return;
    }
    if (index == size_)
    {
        push_back(value);
        return;
    }

    auto newNode = std::make_unique<DoublyListNode<T>>(value);
    DoublyListNode<T> *current = head.get();
    for (size_t i = 0; i < index - 1; ++i)
    {
        current = current->next.get();
    }

    newNode->next = std::move(current->next);
    newNode->prev = current;
    current->next = std::move(newNode);
    current->next->next->prev = current->next.get();
    ++size_;
}

template <typename T>
void DoublyLinkedList<T>::insert(size_t index, T &&value)
{
    if (index > size_)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        push_front(std::move(value));
        return;
    }
    if (index == size_)
    {
        push_back(std::move(value));
        return;
    }

    auto newNode = std::make_unique<DoublyListNode<T>>(std::move(value));
    DoublyListNode<T> *current = head.get();
    for (size_t i = 0; i < index - 1; ++i)
    {
        current = current->next.get();
    }

    newNode->next = std::move(current->next);
    newNode->prev = current;
    current->next = std::move(newNode);
    current->next->next->prev = current->next.get();
    ++size_;
}

template <typename T>
void DoublyLinkedList<T>::erase(size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        head = std::move(head->next);
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
    }
    else
    {
        DoublyListNode<T> *current = head.get();
        for (size_t i = 0; i < index - 1; ++i)
        {
            current = current->next.get();
        }
        current->next = std::move(current->next->next);
        if (current->next)
        {
            current->next->prev = current;
        }
        else
        {
            tail = current;
        }
    }
    --size_;
}

template <typename T>
T &DoublyLinkedList<T>::operator[](size_t index)
{
    return getNode(index)->data;
}

template <typename T>
const T &DoublyLinkedList<T>::operator[](size_t index) const
{
    return getNode(index)->data;
}

template <typename T>
size_t DoublyLinkedList<T>::size() const { return size_; }

template <typename T>
DoublyListIterator<T> DoublyLinkedList<T>::begin()
{
    return DoublyListIterator<T>(head.get());
}

template <typename T>
DoublyListIterator<T> DoublyLinkedList<T>::end()
{
    return DoublyListIterator<T>(nullptr);
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T &value)
{
    auto newNode = std::make_unique<DoublyListNode<T>>(value);
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->next = std::move(head);
        head = std::move(newNode);
        head->next->prev = head.get();
    }
    ++size_;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T &&value)
{
    auto newNode = std::make_unique<DoublyListNode<T>>(std::move(value));
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->next = std::move(head);
        head = std::move(newNode);
        head->next->prev = head.get();
    }
    ++size_;
}

template <typename T>
DoublyListNode<T> *DoublyLinkedList<T>::getNode(size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    DoublyListNode<T> *current = head.get();
    for (size_t i = 0; i < index; ++i)
    {
        current = current->next.get();
    }
    return current;
}

// ==================== РЕАЛИЗАЦИИ SINGLY LINKED LIST ====================

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size_(0) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList &&other) noexcept
    : head(std::move(other.head)), size_(other.size_)
{
    other.size_ = 0;
}

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList &&other) noexcept
{
    if (this != &other)
    {
        head = std::move(other.head);
        size_ = other.size_;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void SinglyLinkedList<T>::push_back(const T &value)
{
    auto newNode = std::make_unique<SinglyListNode<T>>(value);
    if (!head)
    {
        head = std::move(newNode);
    }
    else
    {
        SinglyListNode<T> *current = head.get();
        while (current->next)
        {
            current = current->next.get();
        }
        current->next = std::move(newNode);
    }
    ++size_;
}

template <typename T>
void SinglyLinkedList<T>::push_back(T &&value)
{
    auto newNode = std::make_unique<SinglyListNode<T>>(std::move(value));
    if (!head)
    {
        head = std::move(newNode);
    }
    else
    {
        SinglyListNode<T> *current = head.get();
        while (current->next)
        {
            current = current->next.get();
        }
        current->next = std::move(newNode);
    }
    ++size_;
}

template <typename T>
void SinglyLinkedList<T>::insert(size_t index, const T &value)
{
    if (index > size_)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        push_front(value);
        return;
    }

    auto newNode = std::make_unique<SinglyListNode<T>>(value);
    SinglyListNode<T> *current = head.get();
    for (size_t i = 0; i < index - 1; ++i)
    {
        current = current->next.get();
    }

    newNode->next = std::move(current->next);
    current->next = std::move(newNode);
    ++size_;
}

template <typename T>
void SinglyLinkedList<T>::insert(size_t index, T &&value)
{
    if (index > size_)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        push_front(std::move(value));
        return;
    }

    auto newNode = std::make_unique<SinglyListNode<T>>(std::move(value));
    SinglyListNode<T> *current = head.get();
    for (size_t i = 0; i < index - 1; ++i)
    {
        current = current->next.get();
    }

    newNode->next = std::move(current->next);
    current->next = std::move(newNode);
    ++size_;
}

template <typename T>
void SinglyLinkedList<T>::erase(size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        head = std::move(head->next);
    }
    else
    {
        SinglyListNode<T> *current = head.get();
        for (size_t i = 0; i < index - 1; ++i)
        {
            current = current->next.get();
        }
        current->next = std::move(current->next->next);
    }
    --size_;
}

template <typename T>
T &SinglyLinkedList<T>::operator[](size_t index)
{
    return getNode(index)->data;
}

template <typename T>
const T &SinglyLinkedList<T>::operator[](size_t index) const
{
    return getNode(index)->data;
}

template <typename T>
size_t SinglyLinkedList<T>::size() const { return size_; }

template <typename T>
BaseIterator<T, SinglyListNode<T>> SinglyLinkedList<T>::begin()
{
    return BaseIterator<T, SinglyListNode<T>>(head.get());
}

template <typename T>
BaseIterator<T, SinglyListNode<T>> SinglyLinkedList<T>::end()
{
    return BaseIterator<T, SinglyListNode<T>>(nullptr);
}

template <typename T>
void SinglyLinkedList<T>::push_front(const T &value)
{
    auto newNode = std::make_unique<SinglyListNode<T>>(value);
    newNode->next = std::move(head);
    head = std::move(newNode);
    ++size_;
}

template <typename T>
void SinglyLinkedList<T>::push_front(T &&value)
{
    auto newNode = std::make_unique<SinglyListNode<T>>(std::move(value));
    newNode->next = std::move(head);
    head = std::move(newNode);
    ++size_;
}

template <typename T>
SinglyListNode<T> *SinglyLinkedList<T>::getNode(size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    SinglyListNode<T> *current = head.get();
    for (size_t i = 0; i < index; ++i)
    {
        current = current->next.get();
    }
    return current;
}

// ==================== ЯВНОЕ ИНСТАНЦИРОВАНИЕ ДЛЯ INT ====================

template class Vector<int>;
template class DoublyLinkedList<int>;
template class SinglyLinkedList<int>;

template struct DoublyListNode<int>;
template struct SinglyListNode<int>;
template class BaseIterator<int, DoublyListNode<int>>;
template class BaseIterator<int, SinglyListNode<int>>;
template class DoublyListIterator<int>;

// ==================== РЕАЛИЗАЦИИ ФУНКЦИЙ ДЕМОНСТРАЦИИ ====================

template <typename Container>
void demonstrate(const std::string &container_name)
{
    std::cout << "=== Демонстрация " << container_name << " ===" << std::endl;
    Container c;

    // 1. Добавление элементов 0-9
    std::cout << "1. Добавление элементов 0-9: ";
    for (int i = 0; i < 10; ++i)
    {
        c.push_back(i);
    }
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 2. Вывод размера
    std::cout << "2. Размер контейнера: " << c.size() << std::endl;

    // 3. Удаление 3-го, 5-го и 7-го элементов
    c.erase(2); // 3-й элемент (индекс 2)
    c.erase(3); // 5-й элемент (после удаления индекс 3)
    c.erase(4); // 7-й элемент (после удалений индекс 4)
    std::cout << "3. После удаления 3,5,7 элементов: ";
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 4. Добавление в начало
    c.push_front(10);
    std::cout << "4. После добавления 10 в начало: ";
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 5. Добавление в середину
    size_t middle = c.size() / 2;
    c.insert(middle, 20);
    std::cout << "5. После добавления 20 в середину: ";
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 6. Добавление в конец
    c.push_back(30);
    std::cout << "6. После добавления 30 в конец: ";
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl
              << std::endl;
}

// Явное инстанцирование шаблонных функций
template void demonstrate<Vector<int>>(const std::string &);
template void demonstrate<DoublyLinkedList<int>>(const std::string &);
template void demonstrate<SinglyLinkedList<int>>(const std::string &);

void demonstrate_move_semantics()
{
    std::cout << "=== Демонстрация семантики перемещения ===" << std::endl;

    // Создание и заполнение вектора
    Vector<int> v1;
    for (int i = 0; i < 5; ++i)
    {
        v1.push_back(i * 10);
    }

    std::cout << "Вектор v1 до перемещения: ";
    for (const auto &elem : v1)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Перемещение
    Vector<int> v2 = std::move(v1);
    std::cout << "Вектор v2 после перемещения: ";
    for (const auto &elem : v2)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Размер v1 после перемещения: " << v1.size() << std::endl;
    std::cout << "Размер v2 после перемещения: " << v2.size() << std::endl
              << std::endl;
}

void demonstrate_vector_reserve()
{
    std::cout << "=== Демонстрация резервирования памяти в Vector ===" << std::endl;

    Vector<int> v;
    std::cout << "Начальная емкость: " << v.capacity() << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
        std::cout << "Элементов: " << v.size() << ", Емкость: " << v.capacity() << std::endl;
    }
    std::cout << std::endl;
}