#include "comparasion.hpp"
#include "correctness.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main() {
    const size_t maxVertexCountCase1 = 4000;
    const size_t maxVertexCountCase2 = 4000;
    const size_t maxVertexCountCase3 = 4000;
    const size_t vertexStep = 50;

    auto edge_count_case1 = [](size_t n) { return 2 * n; };
    auto edge_count_case2 = [](size_t n) { return n * static_cast<size_t>(std::sqrt(n)); };
    auto edge_count_case3 = [](size_t n) { return n * n / 4; };

    /*std::vector<std::thread> threads;

    threads.emplace_back(run_kruskal_test, maxVertexCountCase1, vertexStep,
        "../../data/kruskal_file_1.txt", edge_count_case1);
    threads.emplace_back(run_kruskal_test, maxVertexCountCase2, vertexStep,
        "../../data/kruskal_file_2.txt", edge_count_case2);
    threads.emplace_back(run_kruskal_test, maxVertexCountCase3, vertexStep,
        "../../data/kruskal_file_3.txt", edge_count_case3);


    threads.emplace_back(run_prim_binary_test, maxVertexCountCase1, vertexStep,
        "../../data/prim_bin_file_1.txt", edge_count_case1);
    threads.emplace_back(run_prim_binary_test, maxVertexCountCase2, vertexStep,
        "../../data/prim_bin_file_2.txt", edge_count_case2);
    threads.emplace_back(run_prim_binary_test, maxVertexCountCase3, vertexStep,
        "../../data/prim_bin_file_3.txt", edge_count_case3);


    threads.emplace_back(run_prim_fibonacci_test, maxVertexCountCase1, vertexStep,
        "../../data/prim_fib_file_1.txt", edge_count_case1);
    threads.emplace_back(run_prim_fibonacci_test, maxVertexCountCase2, vertexStep,
        "../../data/prim_fib_file_2.txt", edge_count_case2);
    threads.emplace_back(run_prim_fibonacci_test, maxVertexCountCase3, vertexStep,
        "../../data/prim_fib_file_3.txt", edge_count_case3);


    threads.emplace_back(run_prim_vector_test, maxVertexCountCase1, vertexStep,
        "../../data/prim_vec_file_1.txt", edge_count_case1);
    threads.emplace_back(run_prim_vector_test, maxVertexCountCase2, vertexStep,
        "../../data/prim_vec_file_2.txt", edge_count_case2);
    threads.emplace_back(run_prim_vector_test, maxVertexCountCase3, vertexStep,
        "../../data/prim_vec_file_3.txt", edge_count_case3);
    
    for (auto& thread : threads) {
        thread.join();
    }*/

    /*run_kruskal_test(maxVertexCountCase1, vertexStep,
        "../../data/kruskal_file_1.txt", edge_count_case1);
    run_kruskal_test(maxVertexCountCase2, vertexStep,
        "../../data/kruskal_file_2.txt", edge_count_case2);
    run_kruskal_test(maxVertexCountCase3, vertexStep,
        "../../data/kruskal_file_3.txt", edge_count_case3);*/

    /*run_prim_binary_test(maxVertexCountCase1, vertexStep,
        "../../data/prim_bin_file_1.txt", edge_count_case1);
    run_prim_binary_test(maxVertexCountCase2, vertexStep,
        "../../data/prim_bin_file_2.txt", edge_count_case2);
    run_prim_binary_test(maxVertexCountCase3, vertexStep,
        "../../data/prim_bin_file_3.txt", edge_count_case3);

    run_prim_fibonacci_test(maxvertexcountcase1, vertexstep,
        "../../data/prim_fib_file_1.txt", edge_count_case1);
    run_prim_fibonacci_test(maxvertexcountcase2, vertexstep,
        "../../data/prim_fib_file_2.txt", edge_count_case2);
    run_prim_fibonacci_test(maxvertexcountcase3, vertexstep,
        "../../data/prim_fib_file_3.txt", edge_count_case3);*/

    run_prim_vector_test(maxVertexCountCase1, vertexStep,
        "../../data/prim_vec_file_1.txt", edge_count_case1);
    run_prim_vector_test(maxVertexCountCase2, vertexStep,
        "../../data/prim_vec_file_2.txt", edge_count_case2);
    run_prim_vector_test(maxVertexCountCase3, vertexStep,
        "../../data/prim_vec_file_3.txt", edge_count_case3);
     
    /*std::cout << are_prim_kruskal_correct(100, edge_count_case3);*/

    return 0;
}