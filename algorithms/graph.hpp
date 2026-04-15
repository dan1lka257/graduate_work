#pragma once

#include "edge.hpp"
#include <vector>
#include <utility>

template <typename T, typename U>
struct Graph {
    std::vector<std::vector<std::pair<U, T>>> neig;
    U vertexCount;
    U edgeCount;

    Graph(U vertexCount, U edgeCount) : vertexCount(vertexCount), edgeCount(edgeCount) {
        neig.resize(vertexCount + 1, std::vector<std::pair<U, T>>{});
    }

    Graph(Edges<T, U>& edges) : vertexCount(edges.vertexCount), edgeCount(edges.edgeCount) {
        neig.resize(vertexCount + 1, std::vector<std::pair<U, T>>{});
        for (const auto& edge : edges.edges) {
            neig[edge.from].emplace_back(edge.to, edge.cost);
            neig[edge.to].emplace_back(edge.from, edge.cost);
        }
    }
};