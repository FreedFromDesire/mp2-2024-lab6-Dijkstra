#pragma once

#include <gtest.h>
#include "dheap.h"

TEST(BinaryHeap, generate_default) {
	ASSERT_NO_THROW(BinaryHeap);
}

TEST(BinaryHeap, DefaultConstructorCreatesEmptyHeap) {
    BinaryHeap heap;
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(BinaryHeap, InsertIncreasesSize) {
    BinaryHeap heap;
    heap.insert(1, 10.5);
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 1);
}

TEST(BinaryHeap, GetMinReturnsCorrectElement) {
    BinaryHeap heap;
    heap.insert(1, 10.5);
    heap.insert(2, 5.5);
    heap.insert(3, 15.0);

    auto min = heap.getMin();
    EXPECT_EQ(min.first, 2);
    EXPECT_DOUBLE_EQ(min.second, 5.5);
}

TEST(BinaryHeap, ExtractMinReturnsAndRemovesMin) {
    BinaryHeap heap;
    heap.insert(1, 10.5);
    heap.insert(2, 5.5);
    heap.insert(3, 15.0);

    auto min1 = heap.extractMin();
    EXPECT_EQ(min1.first, 2);
    EXPECT_DOUBLE_EQ(min1.second, 5.5);
    EXPECT_EQ(heap.size(), 2);

    auto min2 = heap.extractMin();
    EXPECT_EQ(min2.first, 1);
    EXPECT_DOUBLE_EQ(min2.second, 10.5);
}

TEST(BinaryHeap, HeapPropertyMaintainedAfterInsert) {
    BinaryHeap heap;
    heap.insert(1, 20.0);
    heap.insert(2, 15.0);
    heap.insert(3, 10.0);
    heap.insert(4, 5.0);

    EXPECT_EQ(heap.getMin().first, 4);
    heap.extractMin();
    EXPECT_EQ(heap.getMin().first, 3);
    heap.extractMin();
    EXPECT_EQ(heap.getMin().first, 2);
    heap.extractMin();
    EXPECT_EQ(heap.getMin().first, 1);
}

TEST(BinaryHeap, RemoveMaintainsHeapProperty) {
    BinaryHeap heap;
    heap.insert(1, 10.0);
    heap.insert(2, 20.0);
    heap.insert(3, 5.0);
    heap.insert(4, 15.0);

    int index = heap.findIndex(2); // Удаляем элемент со значением 20.0
    heap.remove(index);

    EXPECT_EQ(heap.size(), 3);
    EXPECT_EQ(heap.getMin().first, 3);
}

TEST(BinaryHeap, ChangeValueUpdatesHeap) {
    BinaryHeap heap;
    heap.insert(1, 10.0);
    heap.insert(2, 20.0);
    heap.insert(3, 5.0);

    int index = heap.findIndex(2);
    heap.changeValue(index, { 2, 2.0 });

    EXPECT_EQ(heap.getMin().first, 2);
    heap.extractMin();
    EXPECT_EQ(heap.getMin().first, 3);
}

TEST(BinaryHeap, DecreaseKeyUpdatesPriority) {
    BinaryHeap heap;
    heap.insert(1, 10.0);
    heap.insert(2, 20.0);
    heap.insert(3, 5.0);

    heap.decreaseKey(2, 2.0);

    EXPECT_EQ(heap.getMin().first, 2);
    heap.extractMin();
    EXPECT_EQ(heap.getMin().first, 3);
}

TEST(BinaryHeap, FindIndexReturnsCorrectIndex) {
    BinaryHeap heap;
    heap.insert(1, 10.0);
    heap.insert(2, 20.0);
    heap.insert(3, 5.0);

    EXPECT_GE(heap.findIndex(2), 0);
    EXPECT_EQ(heap.findIndex(99), -1);
}

TEST(BinaryHeap, ConstructFromVectorBuildsValidHeap) {
    Vector<pair<int, double>> elements = { {1, 10.0}, {2, 5.0}, {3, 15.0}, {4, 3.0} };
    BinaryHeap heap(elements);

    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.getMin().first, 4);
}

TEST(BinaryHeap, ThrowsWhenEmpty) {
    BinaryHeap heap;
    EXPECT_THROW(heap.getMin(), std::out_of_range);
    EXPECT_THROW(heap.extractMin(), std::out_of_range);
}

TEST(BinaryHeap, ComplexOperations) {
    BinaryHeap heap;
    for (int i = 0; i < 100; i++) {
        heap.insert(i, 100.0 - i);
    }

    EXPECT_EQ(heap.size(), 100);
    EXPECT_EQ(heap.getMin().first, 99);

    for (int i = 0; i < 50; i++) {
        heap.extractMin();
    }

    EXPECT_EQ(heap.size(), 50);
    EXPECT_EQ(heap.getMin().first, 49);

    int index = heap.findIndex(25);
    heap.changeValue(index, { 25, 0.5 });

    EXPECT_EQ(heap.getMin().first, 25);
}