#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <functional>
#include <queue>
#include <stack>
#include <stdexcept>

template <typename T>
class Tree {
public:
    Tree(std::size_t maxChildren = 2);

    void add_root(Node<T>& root_node);
    void add_sub_node(Node<T>& parent_node, Node<T>& child_node);

    void traverseBFS(const std::function<void(const T&)>& visit);
    void traverseDFS(const std::function<void(const T&)>& visit);

private:
    Node<T>* root;
    std::size_t maxChildren;
};

template <typename T>
Tree<T>::Tree(std::size_t maxChildren) : root(nullptr), maxChildren(maxChildren) {}

template <typename T>
void Tree<T>::add_root(Node<T>& root_node) {
    root = &root_node;
}

template <typename T>
void Tree<T>::add_sub_node(Node<T>& parent_node, Node<T>& child_node) {
    if (!root) {
        throw std::runtime_error("Tree is empty. Add root first.");
    }
    parent_node.addChild(&child_node);
}

template <typename T>
void Tree<T>::traverseBFS(const std::function<void(const T&)>& visit) {
    if (!root) return;

    std::queue<Node<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node<T>* node = nodes.front();
        nodes.pop();
        visit(node->key);

        for (Node<T>* child : node->children) {
            if (child) {
                nodes.push(child);
            }
        }
    }
}

template <typename T>
void Tree<T>::traverseDFS(const std::function<void(const T&)>& visit) {
    if (!root) return;

    std::stack<Node<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node<T>* node = nodes.top();
        nodes.pop();
        visit(node->key);

        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            if (*it) {
                nodes.push(*it);
            }
        }
    }
}

#endif 