#include "comparasion.hpp"
#include <iostream>
#include <string>
#include <thread>

int main() {
    const int64_t maxVertexCount = 3000;
    const int64_t vertexStep = 50;

    auto edge_count_case1 = [](int64_t n) { return 2 * n; };
    auto edge_count_case2 = [](int64_t n) { return n * static_cast<int64_t>(std::sqrt(n)); };
    auto edge_count_case3 = [](int64_t n) { return n * n / 4; };

    std::vector<std::thread> threads;

    threads.emplace_back(run_test, maxVertexCount, vertexStep,
        "../data/kruskal_file_1.txt", "../data/prim_file_1.txt",
        edge_count_case1);

    threads.emplace_back(run_test, maxVertexCount, vertexStep,
        "../data/kruskal_file_2.txt", "../data/prim_file_2.txt",
        edge_count_case2);

    threads.emplace_back(run_test, maxVertexCount, vertexStep,
        "../data/kruskal_file_3.txt", "../data/prim_file_3.txt",
        edge_count_case3);

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}