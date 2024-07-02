#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <cstddef> // להוספת size_t

template <typename T>
class Node {
public:
    T key;
    std::vector<Node<T>*> children;

    Node(const T& key, std::size_t maxChildren = 2);
    void addChild(Node<T>* child);
};

template <typename T>
Node<T>::Node(const T& key, std::size_t maxChildren) : key(key), children(maxChildren, nullptr) {}

template <typename T>
void Node<T>::addChild(Node<T>* child) {
    for (std::size_t i = 0; i < children.size(); ++i) {
        if (!children[i]) {
            children[i] = child;
            return;
        }
    }
    children.push_back(child);  // אם אין מקום בילדים, מוסיפים דינמית.
}

#endif // NODE_HPP