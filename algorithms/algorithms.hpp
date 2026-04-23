#pragma once

#include "graph.hpp"
#include "edge.hpp"
#include "binary_heap.hpp"
#include "fibonacci_heap.hpp"
#include "dsu.hpp"
#include <algorithm>
#include <vector>
#include <limits>
#include <chrono>

struct VectorStrategy {
    std::vector<double> dist;
    std::vector<size_t> used;

    VectorStrategy(size_t vertexCount)
        : dist(vertexCount + 1, std::numeric_limits<double>::max())
        , used(vertexCount + 1, 0) {
        dist[1] = 0;
    }

    size_t find_min() {
        size_t min_dist_ind = -1;
        double min_val = std::numeric_limits<double>::max();
        for (size_t i = 1; i < dist.size(); ++i) {
            if (!used[i] && dist[i] < min_val) {
                min_val = dist[i];
                min_dist_ind = i;
            }
        }
        return min_dist_ind;
    }

    void update(size_t to, double cost) {
        if (cost < dist[to]) {
            dist[to] = cost;
        }
    }

    bool need_update_parent(size_t to, double cost) {
        return cost <= dist[to];
    }

    void init() {}
};

struct BinaryHeapStrategy {
    BinaryHeap<std::pair<double, size_t>> dist;
    std::vector<size_t> used;

    BinaryHeapStrategy(size_t vertexCount)
        : used(vertexCount + 1, 0) {
        dist.push({ 0, 1 });
    }

    size_t find_min() {
        while (!dist.empty() && used[dist.top().second]) {
            dist.pop();
        }
        if (dist.empty()) {
            return -1;
        }
        return dist.top().second;
    }

    void update(size_t to, double cost) {
        dist.push({ cost, to });
    }

    bool need_update_parent(size_t to, double cost) {
        return true;
    }

    void init() {}
};

struct FibonacciHeapStrategy {
    FibonacciHeap<std::pair<double, size_t>> heap;
    std::vector<size_t> used;
    std::vector<typename FibonacciHeap<std::pair<double, size_t>>::Node*> nodes;
    std::vector<double> current_dist;

    FibonacciHeapStrategy(size_t vertexCount)
        : used(vertexCount + 1, 0)
        , nodes(vertexCount + 1, nullptr)
        , current_dist(vertexCount + 1, std::numeric_limits<double>::max()) {
        current_dist[1] = 0;
        nodes[1] = heap.push({ 0, 1 });
    }

    size_t find_min() {
        while (!heap.empty() && used[heap.top().second]) {
            heap.pop();
        }
        if (heap.empty()) {
            return -1;
        }
        return heap.top().second;
    }

    void update(size_t to, double cost) {
        if (cost < current_dist[to]) {
            current_dist[to] = cost;
            if (nodes[to] != nullptr) {
                heap.decrease_key(nodes[to], { cost, to });
            }
            else {
                nodes[to] = heap.push({ cost, to });
            }
        }
    }

    bool need_update_parent(size_t to, double cost) {
        return cost <= current_dist[to];
    }

    void init() {}
};

template<typename Strategy>
std::pair<Graph, double> Prim_generic(Graph& graph, Strategy& strategy) {
    Graph new_graph(graph.vertexCount, 0);
    std::vector<std::pair<size_t, double>> parent(graph.vertexCount + 1, std::pair<size_t, double>(-1, -1));

    strategy.init();


    auto start = std::chrono::high_resolution_clock::now();


    for (size_t i = 1; i <= graph.vertexCount; ++i) {
        size_t min_dist_ind = strategy.find_min();
        size_t undefined = static_cast<size_t>(-1);
        if (min_dist_ind == undefined) break;

        strategy.used[min_dist_ind] = 1;

        if (parent[min_dist_ind].first != undefined) {
            size_t from = parent[min_dist_ind].first;
            double cost = parent[min_dist_ind].second;
            new_graph.neig[min_dist_ind].emplace_back(from, cost);
            new_graph.neig[from].emplace_back(min_dist_ind, cost);
            new_graph.edgeCount++;
        }

        for (const auto& neighbor : graph.neig[min_dist_ind]) {
            size_t to = neighbor.first;
            double cost = neighbor.second;

            if (!strategy.used[to]) {
                strategy.update(to, cost);
                if (strategy.need_update_parent(to, cost)) {
                    if (parent[to].first == undefined || cost < parent[to].second) {
                        parent[to] = { min_dist_ind, cost };
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return std::make_pair(new_graph, duration.count());
}

std::pair<Graph, double> Prim_vector(Graph& graph) {
    VectorStrategy strategy(graph.vertexCount);
    return Prim_generic(graph, strategy);
}

std::pair<Graph, double> Prim_binary(Graph& graph) {
    BinaryHeapStrategy strategy(graph.vertexCount);
    return Prim_generic(graph, strategy);
}

std::pair<Graph, double> Prim_fibonacci(Graph& graph) {
    FibonacciHeapStrategy strategy(graph.vertexCount);
    return Prim_generic(graph, strategy);
}

std::pair<Graph, double> Kruskal(Edges& edges) {
    Edges new_edges(edges.vertexCount, edges.vertexCount - 1);
    Dsu dsu(edges.vertexCount + 1);

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(edges.edges.begin(), edges.edges.end(), [](const Edge& a, const Edge& b) { return a.cost < b.cost; });
    for (const auto& edge : edges.edges) {
        if (dsu.find_parent(edge.from) != dsu.find_parent(edge.to)) {
            dsu.unite(edge.from, edge.to);
            new_edges.edges.emplace_back(edge);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return std::make_pair(Graph(new_edges), duration.count());
}