#pragma once

#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
#include "vector.h"

using namespace std;

class BinaryHeap {
private:
    Vector<pair<int, double>> heap; 


    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t leftChild(size_t i) const { return 2 * i + 1; }
    size_t rightChild(size_t i) const { return 2 * i + 2; }


    void siftUp(size_t i) {
        while (i > 0 && heap[parent(i)].second > heap[i].second) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void siftDown(size_t i) {
        size_t minIndex = i;
        size_t left = leftChild(i);
        size_t right = rightChild(i);

        if (left < heap.size() && heap[left].second < heap[minIndex].second) {
            minIndex = left;
        }

        if (right < heap.size() && heap[right].second < heap[minIndex].second) {
            minIndex = right;
        }

        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    BinaryHeap() = default;

    explicit BinaryHeap(const Vector<pair<int, double>>& elements) : heap(elements) {
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    void insert(const pair<int, double>& value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    void insert(int vertex, double distance) {
        heap.push_back({ vertex, distance });
        siftUp(heap.size() - 1);
    }

    const pair<int, double>& getMin() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    pair<int, double> extractMin() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        auto result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!empty()) {
            siftDown(0);
        }
        return result;
    }

    void remove(size_t i) {
        if (i >= heap.size()) {
            throw std::out_of_range("Index out of range");
        }
        heap[i] = heap.back();
        heap.pop_back();
        siftDown(i);
    }

    void changeValue(size_t i, const pair<int, double>& newValue) {
        if (i >= heap.size()) {
            throw std::out_of_range("Index out of range");
        }
        auto oldValue = heap[i];
        heap[i] = newValue;
        if (newValue.second < oldValue.second) {
            siftUp(i);
        }
        else {
            siftDown(i);
        }
    }

    int findIndex(int vertex) const {
        for (size_t i = 0; i < heap.size(); ++i) {
            if (heap[i].first == vertex) {
                return static_cast<int>(i);
            }
        }
        return -1;  
    }

    void decreaseKey(int vertex, double newDistance) {
        int index = findIndex(vertex);
        if (index == -1) {
            insert(vertex, newDistance);
        }
        else if (newDistance < heap[index].second) {
            heap[index].second = newDistance;
            siftUp(static_cast<size_t>(index));
        }
    }
};