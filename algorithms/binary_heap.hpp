#pragma once

#include <vector>
#include <stdexcept>
#include <cstdint>

template <typename T, typename U = int64_t>
class BinaryHeap {
private:
    std::vector<T> heap;

    U parent(U i) const { return (i - 1) / 2; }
    U left_child(U i) const { return 2 * i + 1; }
    U right_child(U i) const { return 2 * i + 2; }

    void sift_up(U i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void sift_down(U i) {
        U min_index = i;
        U left = left_child(i);
        U right = right_child(i);

        if (left < static_cast<U>(heap.size()) && heap[left] < heap[min_index]) {
            min_index = left;
        }
        if (right < static_cast<U>(heap.size()) && heap[right] < heap[min_index]) {
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
        sift_up(static_cast<U>(heap.size()) - 1);
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