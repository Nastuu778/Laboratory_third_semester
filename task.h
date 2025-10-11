#ifndef TASK_H
#define TASK_H

#include <memory>
#include <stdexcept>
#include <iterator>
#include <string>

// ==================== ВСПОМОГАТЕЛЬНЫЕ СТРУКТУРЫ ====================

template <typename T>
struct DoublyListNode
{
    T data;
    std::unique_ptr<DoublyListNode> next;
    DoublyListNode *prev;

    DoublyListNode(const T &value);
    DoublyListNode(T &&value);
};

template <typename T>
struct SinglyListNode
{
    T data;
    std::unique_ptr<SinglyListNode> next;

    SinglyListNode(const T &value);
    SinglyListNode(T &&value);
};

// ==================== БАЗОВЫЙ ИТЕРАТОР ====================

template <typename T, typename NodeT>
class BaseIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    BaseIterator(NodeT *node);
    T &operator*() const;
    T *operator->() const;
    BaseIterator &operator++();
    BaseIterator operator++(int);
    bool operator==(const BaseIterator &other) const;
    bool operator!=(const BaseIterator &other) const;

protected:
    NodeT *current;
};

template <typename T>
class DoublyListIterator : public BaseIterator<T, DoublyListNode<T>>
{
public:
    using BaseIterator<T, DoublyListNode<T>>::BaseIterator;
    DoublyListIterator &operator--();
    DoublyListIterator operator--(int);
};

// ==================== VECTOR ====================

template <typename T>
class Vector
{
public:
    Vector();
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;
    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;

    void push_back(const T &value);
    void push_back(T &&value);
    void insert(size_t index, const T &value);
    void insert(size_t index, T &&value);
    void erase(size_t index);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    size_t size() const;
    size_t capacity() const;

    T *begin();
    T *end();
    const T *begin() const;
    const T *end() const;

    void push_front(const T &value);
    void push_front(T &&value);
    void reserve(size_t new_capacity);

private:
    std::unique_ptr<T[]> data;
    size_t capacity_;
    size_t size_;
};

// ==================== DOUBLY LINKED LIST ====================

template <typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedList();
    DoublyLinkedList(DoublyLinkedList &&other) noexcept;
    DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept;

    void push_back(const T &value);
    void push_back(T &&value);
    void insert(size_t index, const T &value);
    void insert(size_t index, T &&value);
    void erase(size_t index);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    size_t size() const;

    DoublyListIterator<T> begin();
    DoublyListIterator<T> end();

    void push_front(const T &value);
    void push_front(T &&value);

private:
    DoublyListNode<T> *getNode(size_t index) const;
    std::unique_ptr<DoublyListNode<T>> head;
    DoublyListNode<T> *tail;
    size_t size_;
};

// ==================== SINGLY LINKED LIST ====================

template <typename T>
class SinglyLinkedList
{
public:
    SinglyLinkedList();
    SinglyLinkedList(SinglyLinkedList &&other) noexcept;
    SinglyLinkedList &operator=(SinglyLinkedList &&other) noexcept;

    void push_back(const T &value);
    void push_back(T &&value);
    void insert(size_t index, const T &value);
    void insert(size_t index, T &&value);
    void erase(size_t index);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    size_t size() const;

    BaseIterator<T, SinglyListNode<T>> begin();
    BaseIterator<T, SinglyListNode<T>> end();

    void push_front(const T &value);
    void push_front(T &&value);

private:
    SinglyListNode<T> *getNode(size_t index) const;
    std::unique_ptr<SinglyListNode<T>> head;
    size_t size_;
};

// ==================== ДЕКЛАРАЦИИ ФУНКЦИЙ ДЕМОНСТРАЦИИ ====================

template <typename Container>
void demonstrate(const std::string &container_name);

void demonstrate_move_semantics();
void demonstrate_vector_reserve();

// Явное инстанцирование для int
extern template class Vector<int>;
extern template class DoublyLinkedList<int>;
extern template class SinglyLinkedList<int>;

extern template struct DoublyListNode<int>;
extern template struct SinglyListNode<int>;
extern template class BaseIterator<int, DoublyListNode<int>>;
extern template class BaseIterator<int, SinglyListNode<int>>;
extern template class DoublyListIterator<int>;

#endif // TASK_H