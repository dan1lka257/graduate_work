#pragma once

#include <vector>
#include <stdexcept>
#include <cstddef>

template <typename T>
class BinaryHeap {
private:
    std::vector<T> heap;

    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left_child(size_t i) const { return 2 * i + 1; }
    size_t right_child(size_t i) const { return 2 * i + 2; }

    void sift_up(size_t i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void sift_down(size_t i) {
        size_t min_index = i;
        size_t left = left_child(i);
        size_t right = right_child(i);

        if (left < heap.size() && heap[left] < heap[min_index]) {
            min_index = left;
        }
        if (right < heap.size() && heap[right] < heap[min_index]) {
            min_index = right;
        }
        if (i != min_index) {
            std::swap(heap[i], heap[min_index]);
            sift_down(min_index);
        }
    }

public:
    BinaryHeap() = default;

    bool empty() const { return heap.empty(); }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap.front();
    }

    void push(const T& value) {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!empty()) {
            sift_down(0);
        }
    }
};