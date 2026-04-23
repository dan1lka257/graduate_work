#pragma once

#include "algorithms.hpp"
#include <iostream>
#include <functional>
#include <string>

Edges graph_to_edges(const Graph& graph) {
    Edges result(graph.vertexCount, graph.edgeCount);
    result.edges.clear();

    std::unordered_set<std::pair<size_t, size_t>> added_edges;

    for (size_t i = 1; i <= graph.vertexCount; ++i) {
        for (const auto& neighbor : graph.neig[i]) {
            size_t to = neighbor.first;
            double cost = neighbor.second;

            size_t from = i;
            if (from > to) {
                std::swap(from, to);
            }

            if (added_edges.find({ from, to }) == added_edges.end()) {
                result.edges.emplace_back(from, to, cost);
                added_edges.emplace(from, to);
            }
        }
    }

    std::sort(result.edges.begin(), result.edges.end(),
        [](const Edge& a, const Edge& b) {
            return a.cost < b.cost;
        }
    );

    return result;
}

bool are_prim_kruskal_correct(size_t maxVertexCount, size_t(*edge_count_func)(size_t)){
    bool are_correct = true;
    for (size_t n = 10; n <= maxVertexCount; n += 1) {
        size_t m = edge_count_func(n);
        Edges edges(n, m);
        edges.fill();
        Graph graph(edges);

        // Kruskal
        auto kruskal_graph = Kruskal(edges).first;

        // Prim
        auto prim_vec_graph = Prim_vector(graph).first;
        auto prim_bin_graph = Prim_binary(graph).first;
        auto prim_fib_graph = Prim_fibonacci(graph).first;


        auto kruskal_edges = graph_to_edges(kruskal_graph);
        auto prim_vec_edges = graph_to_edges(prim_vec_graph);
        auto prim_bin_edges = graph_to_edges(prim_bin_graph);
        auto prim_fib_edges = graph_to_edges(prim_fib_graph);

        are_correct &= (kruskal_edges == prim_bin_edges) && (kruskal_edges == prim_vec_edges) && (prim_bin_edges == prim_fib_edges);
    }
    return are_correct;
}