#pragma once

#include <vector>
#include <numeric>

template <typename U>
struct Dsu {
    std::vector<U> parent;
    std::vector<U> rank;

    Dsu(U n) {
        rank.resize(n, 1);
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
    }

    U find_parent(U x) {
        std::vector<U> way;
        while (parent[x] != x) {
            way.push_back(x);
            x = parent[x];
        }
        for (auto i : way) {
            parent[i] = x;
        }
        return x;
    }

    void unite(U x, U y) {
        x = find_parent(x);
        y = find_parent(y);
        if (rank[x] == rank[y]) {
            parent[x] = y;
            ++rank[y];
        }
        else if (rank[x] < rank[y]) {
            parent[x] = y;
        }
        else {
            parent[y] = x;
        }
    }
};