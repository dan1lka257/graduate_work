#pragma once

#include <vector>
#include <numeric>
#include <cstddef>

struct Dsu {
    std::vector<size_t> parent;
    std::vector<size_t> size;

    Dsu(size_t n) : parent(n), size(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    size_t find_parent(size_t x) {
        if (parent[x] != x) parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(size_t x, size_t y) {
        x = find_parent(x);
        y = find_parent(y);
        if (x == y) return;

        if (size[x] < size[y]) std::swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
};