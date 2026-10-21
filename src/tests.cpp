#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <iostream>

// ============================================================
// PART 2 Tests: DoublyLinkedList
// ============================================================

/// Create a DoublyLinkedList. Verify length() is 0 on a new list.
void test_new_list_is_empty(void)
{
    DoublyLinkedList doubLinkList=DoublyLinkedList();

    TEST_ASSERT_TRUE_MESSAGE(doubLinkList.length()==0, "test_new_list_is_empty FAIL");
}

/// Create a DoublyLinkedList. Call pushFrontValue and pushBackValue.
/// Verify length() is 2.
void test_push_increases_length(void)
{
    DoublyLinkedList doubLinkList=DoublyLinkedList();

    doubLinkList.pushFrontValue(1);
    doubLinkList.pushBackValue(1);
    TEST_ASSERT_TRUE_MESSAGE(doubLinkList.length()==2, "test_push_increases_length FAIL");
}

/// Create an EMPTY DoublyLinkedList.
/// Verify popFrontValue() and popBackValue() both have NO value (has_value() is false).
void test_pop_on_empty_list(void)
{
    DoublyLinkedList doubLinkList=DoublyLinkedList();

    std::optional<NodeValue> frontPop=doubLinkList.popFrontValue();
    std::optional<NodeValue> backPop=doubLinkList.popBackValue();
    TEST_ASSERT_TRUE_MESSAGE(frontPop.has_value()==false, "test_pop_on_empty_list FAIL 1");
    TEST_ASSERT_TRUE_MESSAGE(backPop.has_value()==false, "test_pop_on_empty_list FAIL 2");
}

/// Push 1, 2, 3 with pushBackValue.
/// Verify popBackValue() gives 3, then popFrontValue() gives 1, then length() is 1.
void test_pop_order(void)
{
    DoublyLinkedList doubLinkList=DoublyLinkedList();

    doubLinkList.pushBackValue(1);
    doubLinkList.pushBackValue(2);
    doubLinkList.pushBackValue(3);

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(doubLinkList.popBackValue().value())==3, "test_pop_order FAIL 1");
    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(doubLinkList.popFrontValue().value())==1, "test_pop_order FAIL 2");
    TEST_ASSERT_TRUE_MESSAGE(doubLinkList.length()==1, "test_pop_order FAIL 3");

    
}

/// Push one value, then call deleteValue with a value that is NOT in the list.
/// Verify it returns false and length() does not change.
void test_delete_value_not_found(void)
{
    DoublyLinkedList doubLinkList=DoublyLinkedList();

    doubLinkList.pushBackValue(1);


    TEST_ASSERT_TRUE_MESSAGE(doubLinkList.deleteValue(2)==false, "test_delete_value_not_found FAIL");
}

/// Push 1, 2, 3 with pushBackValue. Call deleteValue(2).
/// Verify popBackValue() gives 3 and the next popBackValue() gives 1.
/// (popBackValue follows prevPtr: this fails if you forgot to repair the backward link.)
void test_delete_middle_keeps_links(void)
{
    DoublyLinkedList doubLinkList=DoublyLinkedList();

    doubLinkList.pushBackValue(1);
    doubLinkList.pushBackValue(2);
    doubLinkList.pushBackValue(3);

    doubLinkList.deleteValue(2);

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(doubLinkList.popBackValue().value())==3, "test_delete_middle_keeps_links FAIL 1");
    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(doubLinkList.popBackValue().value())==1, "test_delete_middle_keeps_links FAIL 2");
}

// ============================================================
// PART 3 Tests: StdDoublyLinkedList
// ============================================================

/// Push 1, 2, 1 with pushBackValue. Call deleteValue(NodeValue{1}).
/// Verify length() is 2 and popFrontValue() gives 2 (only the FIRST 1 was removed).
void test_std_delete_only_first(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Create an EMPTY StdDoublyLinkedList.
/// Verify popFrontValue() and popBackValue() have NO value and do not crash.
void test_std_pop_on_empty_list(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}
