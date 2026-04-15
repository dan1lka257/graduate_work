#pragma once

#include "algorithms.hpp"
#include <fstream>
#include <chrono>
#include <functional>
#include <string>

void run_test(int64_t maxVertexCount,
    int64_t vertexStep,
    const std::string& kruskalFilename,
    const std::string& primFilename,
    int64_t(*edge_count_func)(int64_t))
{
    std::ofstream kruskalFile(kruskalFilename);
    std::ofstream primFile(primFilename);

    for (int64_t n = 10; n < maxVertexCount; n += vertexStep) {
        int64_t m = edge_count_func(n);
        Edges<double, int64_t> edges(n, m);
        edges.fill();

        // Kruskal
        auto startKruskal = std::chrono::high_resolution_clock::now();
        auto kruskal_graph = Kruskal(edges);
        auto endKruskal = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationKruskal = endKruskal - startKruskal;
        kruskalFile << n << " " << durationKruskal.count() << "\n";

        // Prim
        Graph<double, int64_t> graph(edges);
        auto startPrim = std::chrono::high_resolution_clock::now();
        auto prim_graph = Prim(graph);
        auto endPrim = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationPrim = endPrim - startPrim;
        primFile << n << " " << durationPrim.count() << "\n";
    }
}