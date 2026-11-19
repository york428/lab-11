#ifndef TEST_TDOUBLY_LIST_H
#define TEST_TDOUBLY_LIST_H

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "TDoublyList.h"

TEST(TDoublyListTest, BasicOperations) {
    TDoublyList<int> list;
    EXPECT_TRUE(list.IsEmpty());
    EXPECT_EQ(list.Size(), 0);

    list.PushBack(10);
    list.PushBack(20);
    list.PushFront(5);

    EXPECT_FALSE(list.IsEmpty());
    EXPECT_EQ(list.Size(), 3);
    EXPECT_EQ(list.Front(), 5);
    EXPECT_EQ(list.Back(), 20);

    list.PopFront();
    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(list.Front(), 10);

    list.PopBack();
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Back(), 10);
}

TEST(TDoublyListTest, EmptyListExceptions) {
    TDoublyList<int> list;
    EXPECT_THROW(list.PopFront(), std::out_of_range);
    EXPECT_THROW(list.PopBack(), std::out_of_range);
    EXPECT_THROW(list.Front(), std::out_of_range);
    EXPECT_THROW(list.Back(), std::out_of_range);
    EXPECT_TRUE(list.IsEmpty());
}

TEST(TDoublyListTest, PushOrder) {
    TDoublyList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    EXPECT_EQ(list.Front(), 1);
    EXPECT_EQ(list.Back(), 3);

    list.Clear();
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    EXPECT_EQ(list.Front(), 3);
    EXPECT_EQ(list.Back(), 1);
}

TEST(TDoublyListTest, MixedPushFrontAndPushBack) {
    TDoublyList<int> list;
    list.PushBack(2);
    list.PushFront(1);
    list.PushBack(3);

    EXPECT_EQ(list.Size(), 3);
    EXPECT_EQ(list.Front(), 1);
    EXPECT_EQ(list.Back(), 3);
}

TEST(TDoublyListTest, SingleElementFrontAndBack) {
    TDoublyList<int> list;
    list.PushBack(42);

    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Front(), 42);
    EXPECT_EQ(list.Back(), 42);

    list.PopFront();
    EXPECT_TRUE(list.IsEmpty());
}

TEST(TDoublyListTest, PopFrontAndBackToEmpty) {
    TDoublyList<int> list;
    list.PushBack(1);
    list.PushBack(2);

    list.PopFront();
    list.PopFront();

    EXPECT_TRUE(list.IsEmpty());
    EXPECT_EQ(list.Size(), 0);

    // Список должен работать после полного опустошения
    list.PushBack(5);
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Front(), 5);
    EXPECT_EQ(list.Back(), 5);
}

TEST(TDoublyListTest, CopyConstructor) {
    TDoublyList<std::string> list1;
    list1.PushBack("Apple");
    list1.PushBack("Banana");

    TDoublyList<std::string> list2 = list1;

    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(list2.Front(), "Apple");
    EXPECT_EQ(list2.Back(), "Banana");

    // Глубокая копия: изменения не затрагивают оригинал
    list2.PopFront();
    EXPECT_EQ(list2.Size(), 1);
    EXPECT_EQ(list1.Size(), 2);
    EXPECT_EQ(list1.Front(), "Apple");

    list2.PushFront("Zero");
    EXPECT_EQ(list1.Front(), "Apple");
    EXPECT_EQ(list2.Front(), "Zero");
}

TEST(TDoublyListTest, CopyAssignment) {
    TDoublyList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TDoublyList<int> list2;
    list2.PushBack(9);

    list2 = list1;

    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(list2.Front(), 1);
    EXPECT_EQ(list2.Back(), 2);

    // Оригинал не изменился
    EXPECT_EQ(list1.Size(), 2);
    EXPECT_EQ(list1.Front(), 1);
}

TEST(TDoublyListTest, SelfAssignment) {
    TDoublyList<int> list;
    list.PushBack(1);
    list.PushBack(2);

    TDoublyList<int>& ref = list;
    list = ref;

    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(list.Front(), 1);
    EXPECT_EQ(list.Back(), 2);
}

TEST(TDoublyListTest, MoveConstructor) {
    TDoublyList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TDoublyList<int> list2 = std::move(list1);

    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(list2.Front(), 1);
    EXPECT_EQ(list2.Back(), 2);

    EXPECT_EQ(list1.Size(), 0);
    EXPECT_TRUE(list1.IsEmpty());
}

TEST(TDoublyListTest, MoveAssignment) {
    TDoublyList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TDoublyList<int> list2;
    list2.PushBack(9);

    list2 = std::move(list1);

    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(list2.Front(), 1);
    EXPECT_EQ(list2.Back(), 2);

    EXPECT_EQ(list1.Size(), 0);
}

TEST(TDoublyListTest, Clear) {
    TDoublyList<int> list;
    list.PushBack(1);
    list.PushBack(2);

    list.Clear();

    EXPECT_TRUE(list.IsEmpty());
    EXPECT_EQ(list.Size(), 0);
    EXPECT_THROW(list.Front(), std::out_of_range);

    // Список можно использовать после Clear
    list.PushBack(10);
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Front(), 10);
}

TEST(TDoublyListTest, ClearOnEmptyList) {
    TDoublyList<int> list;
    EXPECT_NO_THROW(list.Clear());
    EXPECT_TRUE(list.IsEmpty());
}

TEST(TDoublyListTest, Swap) {
    TDoublyList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TDoublyList<int> list2;
    list2.PushBack(100);
    list2.PushFront(50);

    list1.Swap(list2);

    EXPECT_EQ(list1.Size(), 2);
    EXPECT_EQ(list1.Front(), 50);
    EXPECT_EQ(list1.Back(), 100);

    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(list2.Front(), 1);
    EXPECT_EQ(list2.Back(), 2);
}

TEST(TDoublyListTest, SwapWithEmpty) {
    TDoublyList<int> list1;
    list1.PushBack(1);

    TDoublyList<int> list2;

    list1.Swap(list2);

    EXPECT_TRUE(list1.IsEmpty());
    EXPECT_EQ(list2.Size(), 1);
    EXPECT_EQ(list2.Front(), 1);
}

#endif // TEST_TDOUBLY_LIST_H