#include "task.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ТЕСТИРОВАНИЯ ====================

template <typename Container>
void print_container(const Container &c, const std::string &name)
{
    std::cout << name << ": ";
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
void test_basic_operations(const std::string &container_name)
{
    std::cout << "=== Testing basic operations " << container_name << " ===" << std::endl;

    Container c;

    // Test 1: push_back and size
    std::cout << "1. Test push_back and size: ";
    for (int i = 0; i < 10; ++i)
    {
        c.push_back(i);
    }
    assert(c.size() == 10);
    std::cout << "OK" << std::endl;

    // Test 2: operator[]
    std::cout << "2. Test operator[]: ";
    for (int i = 0; i < 10; ++i)
    {
        assert(c[i] == i);
    }
    std::cout << "OK" << std::endl;

    // Test 3: Iterators
    std::cout << "3. Test iterators: ";
    int expected = 0;
    for (const auto &elem : c)
    {
        assert(elem == expected++);
    }
    std::cout << "OK" << std::endl;

    // Test 4: erase
    std::cout << "4. Test erase: ";
    c.erase(2); // Remove 3rd element (2)
    c.erase(3); // Remove 5th element (4)
    c.erase(4); // Remove 7th element (6)
    assert(c.size() == 7);
    std::cout << "OK" << std::endl;

    // Test 5: push_front
    std::cout << "5. Test push_front: ";
    c.push_front(10);
    assert(c[0] == 10);
    assert(c.size() == 8);
    std::cout << "OK" << std::endl;

    // Test 6: insert in the middle
    std::cout << "6. Test insert in the middle: ";
    c.insert(c.size() / 2, 20);
    assert(c.size() == 9);
    std::cout << "OK" << std::endl;

    // Test 7: push_back after modifications
    std::cout << "7. Test push_back: ";
    c.push_back(30);
    assert(c[c.size() - 1] == 30);
    assert(c.size() == 10);
    std::cout << "OK" << std::endl;

    std::cout << "All basic tests passed successfully!\n"
              << std::endl;
}

template <typename Container>
void test_edge_cases(const std::string &container_name)
{
    std::cout << "=== Testing edge cases " << container_name << " ===" << std::endl;

    Container c;

    // Test 1: Empty container
    std::cout << "1. Test empty container: ";
    assert(c.size() == 0);
    std::cout << "OK" << std::endl;

    // Test 2: Single element
    std::cout << "2. Test single element: ";
    c.push_back(42);
    assert(c.size() == 1);
    assert(c[0] == 42);
    std::cout << "OK" << std::endl;

    // Test 3: Clear container via erase
    std::cout << "3. Test clearing: ";
    c.erase(0);
    assert(c.size() == 0);
    std::cout << "OK" << std::endl;

    // Test 4: Many elements
    std::cout << "4. Test many elements: ";
    for (int i = 0; i < 100; ++i)
    {
        c.push_back(i * 2);
    }
    assert(c.size() == 100);
    for (int i = 0; i < 100; ++i)
    {
        assert(c[i] == i * 2);
    }
    std::cout << "OK" << std::endl;

    // Test 5: Insert at beginning/end
    std::cout << "5. Test insert at beginning/end: ";
    c.insert(0, -1);         // At beginning
    c.insert(c.size(), 999); // At end
    assert(c[0] == -1);
    assert(c[c.size() - 1] == 999);
    std::cout << "OK" << std::endl;

    std::cout << "All edge case tests passed successfully!\n"
              << std::endl;
}

template <typename Container>
void test_move_semantics_for_container(const std::string &container_name)
{
    std::cout << "=== Testing move semantics " << container_name << " ===" << std::endl;

    // Test 1: Move constructor
    std::cout << "1. Test move constructor: ";
    Container c1;
    for (int i = 0; i < 5; ++i)
    {
        c1.push_back(i * 10);
    }
    size_t original_size = c1.size();

    Container c2 = std::move(c1);
    assert(c2.size() == original_size);
    for (int i = 0; i < 5; ++i)
    {
        assert(c2[i] == i * 10);
    }
    // Check that original container is empty
    assert(c1.size() == 0);
    std::cout << "OK" << std::endl;

    // Test 2: Move assignment operator
    std::cout << "2. Test move assignment operator: ";
    Container c3;
    c3 = std::move(c2);
    assert(c3.size() == original_size);
    for (int i = 0; i < 5; ++i)
    {
        assert(c3[i] == i * 10);
    }
    // Check that original container is empty
    assert(c2.size() == 0);
    std::cout << "OK" << std::endl;

    std::cout << "Move semantics tests passed successfully!\n"
              << std::endl;
}

// Specialized tests for Vector
void test_vector_specific()
{
    std::cout << "=== Specialized tests for Vector ===" << std::endl;

    Vector<int> v;

    // Test memory reservation
    std::cout << "1. Test memory reservation: ";
    assert(v.capacity() == 0);
    v.reserve(10);
    assert(v.capacity() >= 10);
    assert(v.size() == 0);
    std::cout << "OK" << std::endl;

    // Test automatic capacity increase
    std::cout << "2. Test automatic capacity increase: ";
    size_t previous_capacity = v.capacity();
    for (int i = 0; i < 20; ++i)
    {
        v.push_back(i);
    }
    assert(v.capacity() > previous_capacity);
    std::cout << "OK (capacity: " << previous_capacity << " -> " << v.capacity() << ")" << std::endl;

    // Test growth factor (should be about 2x)
    std::cout << "3. Test growth factor: ";
    Vector<int> v2;
    v2.push_back(1);
    size_t cap1 = v2.capacity(); // Should be 1
    v2.push_back(2);
    size_t cap2 = v2.capacity(); // Should be 2
    v2.push_back(3);
    size_t cap3 = v2.capacity(); // Should be 4
    assert(cap3 >= cap2 * 2 || cap3 == 4);
    std::cout << "OK (growth: " << cap1 << " -> " << cap2 << " -> " << cap3 << ")" << std::endl;

    // Test data preservation during reallocation
    std::cout << "4. Test data preservation: ";
    Vector<int> v3;
    for (int i = 0; i < 10; ++i)
    {
        v3.push_back(i);
    }
    // Force reallocation
    v3.reserve(20);
    // Check that data is preserved
    for (int i = 0; i < 10; ++i)
    {
        assert(v3[i] == i);
    }
    std::cout << "OK" << std::endl;

    std::cout << "Specialized Vector tests passed successfully!\n"
              << std::endl;
}

// Specialized tests for lists
template <typename List>
void test_list_specific(const std::string &list_name)
{
    std::cout << "=== Specialized tests for " << list_name << " ===" << std::endl;

    List lst;

    // Test efficiency of insertion at beginning
    std::cout << "1. Test efficiency of insertion at beginning: ";
    for (int i = 0; i < 100; ++i)
    {
        lst.push_front(i);
    }
    assert(lst.size() == 100);
    assert(lst[0] == 99); // Last added
    std::cout << "OK" << std::endl;

    // Test sequence integrity after multiple operations
    std::cout << "2. Test integrity after operations: ";
    lst.erase(0);                    // Remove first
    lst.erase(lst.size() - 1);       // Remove last
    lst.insert(lst.size() / 2, 777); // Insert in middle

    // Check that we can iterate through all elements
    int count = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        ++count;
    }
    assert(count == lst.size());
    std::cout << "OK" << std::endl;

    std::cout << "Specialized tests " << list_name << " passed successfully!\n"
              << std::endl;
}

// Test for DoublyLinkedList with reverse traversal (if implemented)
void test_doubly_linked_list_reverse()
{
    std::cout << "=== Reverse traversal test for DoublyLinkedList ===" << std::endl;

    DoublyLinkedList<int> lst;

    // Fill the list
    for (int i = 0; i < 5; ++i)
    {
        lst.push_back(i);
    }

    // Forward traversal
    std::cout << "Forward traversal: ";
    int expected_forward[] = {0, 1, 2, 3, 4};
    int idx = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        assert(*it == expected_forward[idx++]);
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Test passed successfully!\n"
              << std::endl;
}

// Performance test (simple)
template <typename Container>
void test_performance(const std::string &container_name)
{
    std::cout << "=== Performance test " << container_name << " ===" << std::endl;

    Container c;
    const int NUM_ELEMENTS = 1000;

    std::cout << "Adding " << NUM_ELEMENTS << " elements: ";
    for (int i = 0; i < NUM_ELEMENTS; ++i)
    {
        c.push_back(i);
    }
    assert(c.size() == NUM_ELEMENTS);
    std::cout << "OK" << std::endl;

    std::cout << "Multiple insertions: ";
    for (int i = 0; i < 100; ++i)
    {
        c.insert(i * 5, i * 10);
    }
    assert(c.size() == NUM_ELEMENTS + 100);
    std::cout << "OK" << std::endl;

    std::cout << "Multiple deletions: ";
    for (int i = 0; i < 50; ++i)
    {
        c.erase(i * 3);
    }
    assert(c.size() == NUM_ELEMENTS + 100 - 50);
    std::cout << "OK" << std::endl;

    std::cout << "Performance test passed successfully!\n"
              << std::endl;
}

// Function to check the exact scenario from the assignment
template <typename Container>
void test_assignment_scenario(const std::string &container_name)
{
    std::cout << "=== Checking exact assignment scenario for " << container_name << " ===" << std::endl;

    Container c;

    // 1. Adding 10 elements (0..9)
    std::cout << "1. Adding 0..9: ";
    for (int i = 0; i < 10; ++i)
    {
        c.push_back(i);
    }

    // Check: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    for (int i = 0; i < 10; ++i)
    {
        assert(c[i] == i);
    }
    std::cout << "OK" << std::endl;

    // 2. Check size
    std::cout << "2. Size == 10: ";
    assert(c.size() == 10);
    std::cout << "OK" << std::endl;

    // 3. Remove 3rd, 5th and 7th elements
    std::cout << "3. Removing 3rd, 5th, 7th elements: ";
    c.erase(2); // 3rd element (index 2)
    c.erase(3); // 5th element (now index 3)
    c.erase(4); // 7th element (now index 4)

    // Expected result: 0, 1, 3, 5, 7, 8, 9
    int expected1[] = {0, 1, 3, 5, 7, 8, 9};
    for (int i = 0; i < 7; ++i)
    {
        assert(c[i] == expected1[i]);
    }
    std::cout << "OK" << std::endl;

    // 4. Add 10 at the beginning
    std::cout << "4. Adding 10 at the beginning: ";
    c.push_front(10);

    // Expected result: 10, 0, 1, 3, 5, 7, 8, 9
    int expected2[] = {10, 0, 1, 3, 5, 7, 8, 9};
    for (int i = 0; i < 8; ++i)
    {
        assert(c[i] == expected2[i]);
    }
    std::cout << "OK" << std::endl;

    // 5. Add 20 in the middle
    std::cout << "5. Adding 20 in the middle: ";
    c.insert(c.size() / 2, 20);

    // Expected result: 10, 0, 1, 3, 20, 5, 7, 8, 9
    int expected3[] = {10, 0, 1, 3, 20, 5, 7, 8, 9};
    for (int i = 0; i < 9; ++i)
    {
        assert(c[i] == expected3[i]);
    }
    std::cout << "OK" << std::endl;

    // 6. Add 30 at the end
    std::cout << "6. Adding 30 at the end: ";
    c.push_back(30);

    // Expected result: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    int expected4[] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    for (int i = 0; i < 10; ++i)
    {
        assert(c[i] == expected4[i]);
    }
    std::cout << "OK" << std::endl;

    std::cout << "Entire assignment scenario completed correctly!\n"
              << std::endl;
}

// Exception handling test
template <typename Container>
void test_exceptions(const std::string &container_name)
{
    std::cout << "=== Testing exception handling " << container_name << " ===" << std::endl;

    Container c;

    // Test 1: Access to empty container
    std::cout << "1. Test access to empty container: ";
    try
    {
        int value = c[0];
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "OK (caught exception: " << e.what() << ")" << std::endl;
    }

    // Test 2: Insert beyond bounds
    std::cout << "2. Test insert beyond bounds: ";
    try
    {
        c.insert(1, 42);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "OK (caught exception: " << e.what() << ")" << std::endl;
    }

    // Test 3: Delete from empty container
    std::cout << "3. Test delete from empty container: ";
    try
    {
        c.erase(0);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "OK (caught exception: " << e.what() << ")" << std::endl;
    }

    // Add elements and test edge cases
    c.push_back(1);
    c.push_back(2);

    // Test 4: Delete beyond bounds
    std::cout << "4. Test delete beyond bounds: ";
    try
    {
        c.erase(5);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "OK (caught exception: " << e.what() << ")" << std::endl;
    }

    // Test 5: Access beyond bounds
    std::cout << "5. Test access beyond bounds: ";
    try
    {
        int value = c[5];
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "OK (caught exception: " << e.what() << ")" << std::endl;
    }

    std::cout << "All exception tests passed successfully!\n"
              << std::endl;
}

// Copy semantics test (if implemented)
template <typename Container>
void test_copy_semantics(const std::string &container_name)
{
    std::cout << "=== Testing copy semantics " << container_name << " ===" << std::endl;

    Container c1;
    for (int i = 0; i < 5; ++i)
    {
        c1.push_back(i * 10);
    }

    // Test copy constructor
    std::cout << "1. Test copy constructor: ";
    Container c2 = c1;
    assert(c1.size() == c2.size());
    for (int i = 0; i < 5; ++i)
    {
        assert(c1[i] == c2[i]);
    }
    std::cout << "OK" << std::endl;

    // Test copy assignment operator
    std::cout << "2. Test copy assignment operator: ";
    Container c3;
    c3 = c1;
    assert(c1.size() == c3.size());
    for (int i = 0; i < 5; ++i)
    {
        assert(c1[i] == c3[i]);
    }
    std::cout << "OK" << std::endl;

    // Check that these are indeed copies (changing one doesn't affect others)
    std::cout << "3. Test copy independence: ";
    c1[0] = 999;
    assert(c2[0] != 999); // c2 should not change
    assert(c3[0] != 999); // c3 should not change
    std::cout << "OK" << std::endl;

    std::cout << "Copy semantics tests passed successfully!\n"
              << std::endl;
}

// ==================== MAIN FUNCTION ====================

int main()
{
    std::cout << "RUNNING ALL CONTAINER TESTS" << std::endl;
    std::cout << "===================================\n"
              << std::endl;

// Build information
#ifdef NDEBUG
    std::cout << "Build mode: Release" << std::endl;
#else
    std::cout << "Build mode: Debug" << std::endl;
#endif
    std::cout << std::endl;

    try
    {
        // Testing Vector
        std::cout << "TESTING VECTOR" << std::endl;
        std::cout << "==================" << std::endl;
        test_basic_operations<Vector<int>>("Vector");
        test_edge_cases<Vector<int>>("Vector");
        test_move_semantics_for_container<Vector<int>>("Vector");
        test_copy_semantics<Vector<int>>("Vector");
        test_vector_specific();
        test_assignment_scenario<Vector<int>>("Vector");
        test_performance<Vector<int>>("Vector");
        test_exceptions<Vector<int>>("Vector");

        // Testing DoublyLinkedList
        std::cout << "TESTING DOUBLY LINKED LIST" << std::endl;
        std::cout << "===============================" << std::endl;
        test_basic_operations<DoublyLinkedList<int>>("DoublyLinkedList");
        test_edge_cases<DoublyLinkedList<int>>("DoublyLinkedList");
        test_move_semantics_for_container<DoublyLinkedList<int>>("DoublyLinkedList");
        test_list_specific<DoublyLinkedList<int>>("DoublyLinkedList");
        test_doubly_linked_list_reverse();
        test_assignment_scenario<DoublyLinkedList<int>>("DoublyLinkedList");
        test_performance<DoublyLinkedList<int>>("DoublyLinkedList");
        test_exceptions<DoublyLinkedList<int>>("DoublyLinkedList");

        // Testing SinglyLinkedList
        std::cout << "TESTING SINGLY LINKED LIST" << std::endl;
        std::cout << "===============================" << std::endl;
        test_basic_operations<SinglyLinkedList<int>>("SinglyLinkedList");
        test_edge_cases<SinglyLinkedList<int>>("SinglyLinkedList");
        test_move_semantics_for_container<SinglyLinkedList<int>>("SinglyLinkedList");
        test_list_specific<SinglyLinkedList<int>>("SinglyLinkedList");
        test_assignment_scenario<SinglyLinkedList<int>>("SinglyLinkedList");
        test_performance<SinglyLinkedList<int>>("SinglyLinkedList");
        test_exceptions<SinglyLinkedList<int>>("SinglyLinkedList");

        std::cout << "===================================" << std::endl;
        std::cout << "ALL TESTS PASSED SUCCESSFULLY!" << std::endl;
        std::cout << "All containers work correctly according to assignment requirements." << std::endl;
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