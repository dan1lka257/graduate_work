#pragma once

#include "algorithms.hpp"
#include <fstream>
#include <chrono>
#include <functional>
#include <string>
#include <iostream>

const size_t NUM_MEASURE_ITER = 10;

void run_kruskal_test(size_t maxVertexCount,
    size_t vertexStep,
    const std::string& filename,
    size_t(*edge_count_func)(size_t))
{
    std::ofstream outFile(filename);
    outFile << "# vertices edges time_seconds\n";

    for (size_t n = 300; n < maxVertexCount; n += vertexStep) {
        size_t m = edge_count_func(n);
        Edges edges(n, m);

        double time = 0;
        for (size_t i = 0; i < NUM_MEASURE_ITER; ++i) {
            edges.fill();
            time += Kruskal(edges).second;
        }
        time = time / NUM_MEASURE_ITER;
        std::cout << "Kruskal: " << n << " " << m << " " << time << "\n";
        outFile << n << " " << m << " " << time << "\n";
    }

    outFile.close();
}

void run_prim_binary_test(size_t maxVertexCount,
    size_t vertexStep,
    const std::string& filename,
    size_t(*edge_count_func)(size_t))
{
    std::ofstream outFile(filename);
    outFile << "# vertices edges time_seconds\n";

    for (size_t n = 300; n < maxVertexCount; n += vertexStep) {
        size_t m = edge_count_func(n);
        Edges edges(n, m);

        double time = 0;
        for (size_t i = 0; i < NUM_MEASURE_ITER; ++i) {
            edges.fill();
            Graph graph(edges);
            time += Prim_binary(graph).second;
        }
        time = time / NUM_MEASURE_ITER;
        std::cout << "Prim_binary: " << n << " " << m << " " << time << "\n";
        outFile << n << " " << m << " " << time << "\n";
    }

    outFile.close();
}

void run_prim_fibonacci_test(size_t maxVertexCount,
    size_t vertexStep,
    const std::string& filename,
    size_t(*edge_count_func)(size_t))
{
    std::ofstream outFile(filename);
    outFile << "# vertices edges time_seconds\n";

    for (size_t n = 300; n < maxVertexCount; n += vertexStep) {
        size_t m = edge_count_func(n);
        Edges edges(n, m);

        double time = 0;
        for (size_t i = 0; i < NUM_MEASURE_ITER; ++i) {
            edges.fill();
            Graph graph(edges);
            time += Prim_fibonacci(graph).second;
        }
        time = time / NUM_MEASURE_ITER;
        std::cout << "Prim_fibonacci: " << n << " " << m << " " << time << "\n";
        outFile << n << " " << m << " " << time << "\n";
    }

    outFile.close();
}

void run_prim_vector_test(size_t maxVertexCount,
    size_t vertexStep,
    const std::string& filename,
    size_t(*edge_count_func)(size_t))
{
    std::ofstream outFile(filename);
    outFile << "# vertices edges time_seconds\n";

    for (size_t n = 300; n < maxVertexCount; n += vertexStep) {
        size_t m = edge_count_func(n);
        Edges edges(n, m);

        double time = 0;
        for (size_t i = 0; i < NUM_MEASURE_ITER; ++i) {
            edges.fill();
            Graph graph(edges);
            time += Prim_vector(graph).second;
        }
        time = time / NUM_MEASURE_ITER;
        std::cout << "Prim_vector: " << n << " " << m << " " << time << "\n";
        outFile << n << " " << m << " " << time << "\n";
    }

    outFile.close();
}