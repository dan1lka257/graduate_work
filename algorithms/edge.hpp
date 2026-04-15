#pragma once

#include <vector>
#include <unordered_set>
#include <utility>
#include <random>
#include <stdexcept>

template<typename U>
struct std::hash<std::pair<U, U>> {
    size_t operator()(const std::pair<U, U>& p) const {
        auto hash1 = std::hash<U>{}(p.first);
        auto hash2 = std::hash<U>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

template <typename T, typename U>
struct Edge {
    U from;
    U to;
    T cost;
    Edge() = default;
    Edge(U from, U to, T cost) : from(from), to(to), cost(cost) {}
};

template <typename T, typename U>
struct Edges {
    std::vector<Edge<T, U>> edges;
    U vertexCount;
    U edgeCount;

    Edges(U vertexCount, U edgeCount) : vertexCount(vertexCount), edgeCount(edgeCount) {
        if (edgeCount > (vertexCount * (vertexCount - 1)) / 2) {
            throw std::invalid_argument("Edge count exceeds maximum possible for given vertex count");
        }
    }

    void fill() {
        edges.clear();
        std::mt19937 gen(42);
        std::uniform_int_distribution<U> vertex_dist(1, vertexCount);
        std::uniform_real_distribution<T> cost_dist(0.0, 1.0);

        std::unordered_set<std::pair<U, U>> existing_edges;

        for (U i = 1; i <= vertexCount; ++i) {
            U from = i;
            U to = (i % vertexCount) + 1;
            if (from > to) {
                std::swap(from, to);
            }
            edges.emplace_back(from, to, cost_dist(gen));
            existing_edges.emplace(from, to);
        }

        for (U i = vertexCount + 1; i <= edgeCount; ++i) {
            while (true) {
                U from = vertex_dist(gen);
                U to = vertex_dist(gen);
                if (from == to) continue;

                if (from > to) {
                    std::swap(from, to);
                }

                if (!existing_edges.count({ from, to })) {
                    edges.emplace_back(from, to, cost_dist(gen));
                    existing_edges.emplace(from, to);
                    break;
                }
            }
        }
    }
};