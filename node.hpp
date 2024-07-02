#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template <typename T>
class Node {
public:
    T key;
    std::vector<Node<T>*> children;

    Node(const T& key);
    void addChild(Node<T>* child);
    T get_value() const { return key; }
};

template <typename T>
Node<T>::Node(const T& key) : key(key) {}

template <typename T>
void Node<T>::addChild(Node<T>* child) {
    children.push_back(child);
}

#endif // NODE_HPP
