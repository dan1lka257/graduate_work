#pragma once

#include "graph.hpp"
#include "edge.hpp"
#include "binary_heap.hpp"
#include "dsu.hpp"
#include <algorithm>
#include <vector>

template <typename T, typename U>
U find_min(BinaryHeap<std::pair<T, U>>& dist, std::vector<U>& used) {
    while (used[dist.top().second]) {
        dist.pop();
    }
    U min_dist_ind = dist.top().second;
    used[min_dist_ind] = 1;
    return min_dist_ind;
}

template <typename T, typename U>
Graph<T, U> Prim(Graph<T, U>& graph) {
    Graph<T, U> new_graph(graph.vertexCount, 0);
    std::vector<std::pair<U, T>> parent(graph.vertexCount + 1, std::pair<U, T>(-1, -1));
    std::vector<U> used(graph.vertexCount + 1, 0);
    BinaryHeap<std::pair<T, U>> dist;
    dist.push({ 0, 1 });

    for (U i = 0; i < static_cast<U>(graph.neig.size()); ++i) {
        U min_dist_ind = 0;
        try {
            min_dist_ind = find_min(dist, used);
        }
        catch (...) {}

        for (U j = 0; j < static_cast<U>(graph.neig[min_dist_ind].size()); ++j) {
            if (!used[graph.neig[min_dist_ind][j].first]) {
                dist.push({ graph.neig[min_dist_ind][j].second, graph.neig[min_dist_ind][j].first });
                parent[graph.neig[min_dist_ind][j].first] = { min_dist_ind, graph.neig[min_dist_ind][j].second };
            }
        }
    }

    for (U i = 0; i < static_cast<U>(parent.size()); ++i) {
        if (parent[i].first != -1) {
            new_graph.neig[i].emplace_back(parent[i].first, parent[i].second);
            new_graph.neig[parent[i].first].emplace_back(i, parent[i].second);
        }
    }

    return new_graph;
}

template <typename T, typename U>
bool comp(const Edge<T, U>& edge1, const Edge<T, U>& edge2) {
    return edge1.cost < edge2.cost;
}

template <typename T, typename U>
Graph<T, U> Kruskal(Edges<T, U>& edges) {
    Edges<T, U> new_edges(edges.vertexCount, 0);
    std::sort(edges.edges.begin(), edges.edges.end(), comp<T, U>);
    Dsu<U> dsu(edges.vertexCount + 1);

    for (const auto& edge : edges.edges) {
        if (dsu.find_parent(edge.from) != dsu.find_parent(edge.to)) {
            dsu.unite(edge.from, edge.to);
            new_edges.edges.emplace_back(edge);
        }
    }

    return Graph<T, U>(new_edges);
}