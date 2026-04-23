#pragma once

#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <random>
#include <stdexcept>
#include <algorithm>

namespace std {
    template<>
    struct hash<std::pair<size_t, size_t>> {
        size_t operator()(const std::pair<size_t, size_t>& p) const {
            auto hash1 = std::hash<size_t>{}(p.first);
            auto hash2 = std::hash<size_t>{}(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };
}

struct Edge {
    size_t from;
    size_t to;
    double cost;
    Edge() = default;
    Edge(size_t from, size_t to, double cost) : from(from), to(to), cost(cost) {}

    bool operator==(const Edge& other) const {
        return (from == other.from && to == other.to && cost == other.cost) || (from == other.to && to == other.from && cost == other.cost);
    }
};

struct Edges {
    std::vector<Edge> edges;
    size_t vertexCount;
    size_t edgeCount;

    Edges(size_t vertexCount, size_t edgeCount) : vertexCount(vertexCount), edgeCount(edgeCount) {
        if (edgeCount > (vertexCount * (vertexCount - 1)) / 2) {
            throw std::invalid_argument("Edge count exceeds maximum possible for given vertex count");
        }
    }

    bool is_sorted() const {
        for (size_t i = 1; i < edges.size(); ++i) {
            const auto& prev = edges[i - 1];
            const auto& curr = edges[i];
            if (prev.cost > curr.cost) return false;
        }
        return true;
    }

    bool operator==(const Edges& other) const {
        if (vertexCount != other.vertexCount || edgeCount != other.edgeCount) {
            return false;
        }

        bool this_sorted = is_sorted();
        bool other_sorted = other.is_sorted();

        if (this_sorted && other_sorted) {
            return edges == other.edges;
        }
        else {
            if (edges.size() != other.edges.size()) {
                return false;
            }

            std::unordered_set<std::pair<size_t, size_t>> this_edges;
            std::unordered_map<std::pair<size_t, size_t>, double> this_costs;

            for (const auto& edge : edges) {
                size_t from = std::min(edge.from, edge.to);
                size_t to = std::max(edge.from, edge.to);
                this_edges.emplace(from, to);
                this_costs[{from, to}] = edge.cost;
            }

            for (const auto& edge : other.edges) {
                size_t from = std::min(edge.from, edge.to);
                size_t to = std::max(edge.from, edge.to);
                if (!this_edges.count({ from, to })) {
                    return false;
                }
                if (this_costs[{from, to}] != edge.cost) {
                    return false;
                }
            }

            return true;
        }
    }

    void fill() {
        edges.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> vertex_dist(1, vertexCount);
        std::uniform_real_distribution<double> cost_dist(0.0, 1.0);

        std::unordered_set<std::pair<size_t, size_t>> existing_edges;

        for (size_t i = 1; i <= vertexCount; ++i) {
            size_t from = i;
            size_t to = (i % vertexCount) + 1;
            if (from > to) {
                std::swap(from, to);
            }
            edges.emplace_back(from, to, cost_dist(gen));
            existing_edges.emplace(from, to);
        }

        for (size_t i = vertexCount + 1; i <= edgeCount; ++i) {
            while (true) {
                size_t from = vertex_dist(gen);
                size_t to = vertex_dist(gen);
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