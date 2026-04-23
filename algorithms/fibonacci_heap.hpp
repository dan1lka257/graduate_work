#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>

template <typename T>
class FibonacciHeap {
public:
    struct Node {
        T value;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;
        int degree;
        bool marked;

        Node(const T& val) : value(val), parent(nullptr), child(nullptr),
            left(this), right(this), degree(0), marked(false) {}
    };

private:
    Node* min_node;
    size_t node_count;

    void add_to_root_list(Node* node) {
        if (!min_node) {
            min_node = node;
            node->left = node;
            node->right = node;
        }
        else {
            node->left = min_node;
            node->right = min_node->right;
            min_node->right->left = node;
            min_node->right = node;
            if (node->value < min_node->value) {
                min_node = node;
            }
        }
    }

    void consolidate() {
        int max_degree = static_cast<int>(std::log2(node_count)) + 1000;
        std::vector<Node*> degree_table(max_degree, nullptr);

        std::vector<Node*> roots;
        Node* current = min_node;
        do {
            roots.push_back(current);
            current = current->right;
        } while (current != min_node);

        for (Node* root : roots) {
            Node* x = root;
            int d = x->degree;

            while (degree_table[d] != nullptr) {
                Node* y = degree_table[d];
                if (x->value > y->value) {
                    std::swap(x, y);
                }
                // link y to x
                y->left->right = y->right;
                y->right->left = y->left;
                y->parent = x;
                if (!x->child) {
                    x->child = y;
                    y->left = y;
                    y->right = y;
                }
                else {
                    y->left = x->child;
                    y->right = x->child->right;
                    x->child->right->left = y;
                    x->child->right = y;
                }
                x->degree++;
                y->marked = false;
                degree_table[d] = nullptr;
                d++;
            }
            degree_table[d] = x;
        }

        min_node = nullptr;
        for (Node* node : degree_table) {
            if (node) {
                if (!min_node || node->value < min_node->value) {
                    min_node = node;
                }
            }
        }
    }

    void cut(Node* child, Node* parent) {
        if (parent->child == child) {
            if (child->right == child) {
                parent->child = nullptr;
            }
            else {
                parent->child = child->right;
            }
        }
        child->left->right = child->right;
        child->right->left = child->left;
        parent->degree--;

        add_to_root_list(child);
        child->parent = nullptr;
        child->marked = false;
    }

    void cascading_cut(Node* node) {
        Node* parent = node->parent;
        if (parent) {
            if (!node->marked) {
                node->marked = true;
            }
            else {
                cut(node, parent);
                cascading_cut(parent);
            }
        }
    }

    void free_node(Node* node) {
        if (!node) return;
        if (node->child) {
            Node* child = node->child;
            do {
                Node* next = child->right;
                free_node(child);
                child = next;
            } while (child != node->child);
        }
        delete node;
    }

public:
    FibonacciHeap() : min_node(nullptr), node_count(0) {}

    ~FibonacciHeap() {
        if (min_node) {
            std::vector<Node*> roots;
            Node* current = min_node;
            do {
                roots.push_back(current);
                current = current->right;
            } while (current != min_node);
            for (Node* root : roots) {
                free_node(root);
            }
        }
    }

    bool empty() const { return node_count == 0; }
    size_t size() const { return node_count; }

    const T& top() const {
        if (empty()) throw std::out_of_range("Heap is empty");
        return min_node->value;
    }

    Node* push(const T& value) {
        Node* new_node = new Node(value);
        add_to_root_list(new_node);
        node_count++;
        return new_node;
    }

    void pop() {
        if (empty()) throw std::out_of_range("Heap is empty");

        Node* z = min_node;

        if (z->child) {
            Node* child = z->child;
            do {
                Node* next = child->right;
                add_to_root_list(child);
                child->parent = nullptr;
                child = next;
            } while (child != z->child);
        }

        if (z->right == z) {
            min_node = nullptr;
        }
        else {
            z->left->right = z->right;
            z->right->left = z->left;
            min_node = z->right;
            consolidate();
        }

        node_count--;
        delete z;
    }

    void decrease_key(Node* node, const T& new_value) {
        if (new_value > node->value) return;

        node->value = new_value;
        Node* parent = node->parent;

        if (parent && node->value < parent->value) {
            cut(node, parent);
            cascading_cut(parent);
        }

        if (node->value < min_node->value) {
            min_node = node;
        }
    }
};