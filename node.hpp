#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template <typename T>
class Node {
public:
    T key;
    std::vector<Node*> children;

    Node(T val) : key(val) {}
    void addChild(Node* child) {
        children.push_back(child);
    }
    T get_value() const {
        return key;
    }
};

#endif 
