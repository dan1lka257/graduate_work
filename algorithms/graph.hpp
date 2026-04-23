#pragma once

#include "edge.hpp"
#include <vector>
#include <utility>

struct Graph {
    std::vector<std::vector<std::pair<size_t, double>>> neig;
    size_t vertexCount;
    size_t edgeCount;

    Graph(size_t vertexCount, size_t edgeCount) : vertexCount(vertexCount), edgeCount(edgeCount) {
        neig.resize(vertexCount + 1, std::vector<std::pair<size_t, double>>{});
    }

    Graph(Edges& edges) : vertexCount(edges.vertexCount), edgeCount(edges.edgeCount) {
        neig.resize(vertexCount + 1, std::vector<std::pair<size_t, double>>{});
        for (const auto& edge : edges.edges) {
            neig[edge.from].emplace_back(edge.to, edge.cost);
            neig[edge.to].emplace_back(edge.from, edge.cost);
        }
    }
};