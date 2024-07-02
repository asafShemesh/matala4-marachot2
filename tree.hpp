#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <functional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T, int K = 2>
class Tree {
public:
    Tree();
    ~Tree();

    void add_sub_node(Node<T>& parent_node, Node<T>& child_node);
    void traverseBFS(const std::function<void(const T&)>& visit) const;
    void traverseDFS(const std::function<void(const T&)>& visit);

    class Iterator {
    public:
        Iterator(Node<T>* node = nullptr, std::function<void(Node<T>*, std::vector<Node<T>*>&)> traverse = nullptr);

        T& operator*();
        Node<T>* operator->();
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;

    private:
        typename std::vector<Node<T>*>::iterator it;
        std::vector<Node<T>*> nodes;
    };

    Iterator begin_pre_order();
    Iterator end_pre_order();
    Iterator begin_post_order();
    Iterator end_post_order();
    Iterator begin_in_order();
    Iterator end_in_order();
    Iterator begin_bfs_scan();
    Iterator end_bfs_scan();
    Iterator begin_dfs_scan();
    Iterator end_dfs_scan();
    Iterator myHeap();

    Iterator begin() { return begin_bfs_scan(); }
    Iterator end() { return end_bfs_scan(); }

    void add_root(Node<T>& root_node) {
        root = &root_node;
    }

private:
    Node<T>* root;

    void preOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const;
    void postOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const;
    void inOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const;
    void bfsOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const;
    void dfsOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const;

    template <typename U, int V>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U, V>& tree);
};

template <typename T, int K>
Tree<T, K>::Tree() : root(nullptr) {}

template <typename T, int K>
Tree<T, K>::~Tree() {
    // Destructor doesn't delete nodes since they are created on the stack
}

template <typename T, int K>
void Tree<T, K>::add_sub_node(Node<T>& parent_node, Node<T>& child_node) {
    if (!root) {
        throw std::runtime_error("Tree is empty. Add root first.");
    }
    parent_node.addChild(&child_node);
}

template <typename T, int K>
void Tree<T, K>::traverseBFS(const std::function<void(const T&)>& visit) const {
    if (!root) return;

    std::queue<Node<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node<T>* node = nodes.front();
        nodes.pop();
        visit(node->key);

        for (Node<T>* child : node->children) {
            nodes.push(child);
        }
    }
}

template <typename T, int K>
void Tree<T, K>::traverseDFS(const std::function<void(const T&)>& visit) {
    if (!root) return;

    std::stack<Node<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node<T>* node = nodes.top();
        nodes.pop();
        visit(node->key);

        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            nodes.push(*it);
        }
    }
}

template <typename T, int K>
void Tree<T, K>::preOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
    if (!node) return;
    nodes.push_back(node);
    for (Node<T>* child : node->children) {
        preOrder(child, nodes);
    }
}

template <typename T, int K>
void Tree<T, K>::postOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
    if (!node) return;
    for (Node<T>* child : node->children) {
        postOrder(child, nodes);
    }
    nodes.push_back(node);
}

template <typename T, int K>
void Tree<T, K>::inOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
    if (!node) return;
    if (node->children.size() > 0) {
        inOrder(node->children[0], nodes);
    }
    nodes.push_back(node);
    for (size_t i = 1; i < node->children.size(); ++i) {
        inOrder(node->children[i], nodes);
    }
}

template <typename T, int K>
void Tree<T, K>::bfsOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
    if (!node) return;
    std::queue<Node<T>*> q;
    q.push(node);
    while (!q.empty()) {
        Node<T>* n = q.front();
        q.pop();
        nodes.push_back(n);
        for (Node<T>* child : n->children) {
            q.push(child);
        }
    }
}

template <typename T, int K>
void Tree<T, K>::dfsOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
    if (!node) return;
    std::stack<Node<T>*> s;
    s.push(node);
    while (!s.empty()) {
        Node<T>* n = s.top();
        s.pop();
        nodes.push_back(n);
        for (auto it = n->children.rbegin(); it != n->children.rend(); ++it) {
            s.push(*it);
        }
    }
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_pre_order() {
    return Iterator(root, [this](Node<T>* node, std::vector<Node<T>*>& nodes) { preOrder(node, nodes); });
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::end_pre_order() {
    return Iterator(nullptr);
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_post_order() {
    return Iterator(root, [this](Node<T>* node, std::vector<Node<T>*>& nodes) { postOrder(node, nodes); });
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::end_post_order() {
    return Iterator(nullptr);
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_in_order() {
    return Iterator(root, [this](Node<T>* node, std::vector<Node<T>*>& nodes) { inOrder(node, nodes); });
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::end_in_order() {
    return Iterator(nullptr);
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_bfs_scan() {
    return Iterator(root, [this](Node<T>* node, std::vector<Node<T>*>& nodes) { bfsOrder(node, nodes); });
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::end_bfs_scan() {
    return Iterator(nullptr);
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_dfs_scan() {
    return Iterator(root, [this](Node<T>* node, std::vector<Node<T>*>& nodes) { dfsOrder(node, nodes); });
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::end_dfs_scan() {
    return Iterator(nullptr);
}

template <typename T, int K>
typename Tree<T, K>::Iterator Tree<T, K>::myHeap() {
    std::vector<Node<T>*> nodes;
    preOrder(root, nodes);
    std::make_heap(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) { return a->key > b->key; });
    return Iterator(nodes);
}

template <typename T, int K>
Tree<T, K>::Iterator::Iterator(Node<T>* node, std::function<void(Node<T>*, std::vector<Node<T>*>&)> traverse) {
    if (node && traverse) {
        traverse(node, nodes);
        it = nodes.begin();
    } else {
        it = nodes.end();
    }
}

template <typename T, int K>
T& Tree<T, K>::Iterator::operator*() {
    return (*it)->key;
}

template <typename T, int K>
Node<T>* Tree<T, K>::Iterator::operator->() {
    return *it;
}

template <typename T, int K>
typename Tree<T, K>::Iterator& Tree<T, K>::Iterator::operator++() {
    ++it;
    return *this;
}

template <typename T, int K>
bool Tree<T, K>::Iterator::operator!=(const Iterator& other) const {
    return it != other.it;
}

template <typename U, int V>
std::ostream& operator<<(std::ostream& os, const Tree<U, V>& tree) {
    tree.traverseBFS([&os](const U& key) {
        os << key << " ";
    });
    return os;
}

#endif // TREE_HPP
