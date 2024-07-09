#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <functional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QPainter>
#include <QLinearGradient>

template <typename T, std::size_t N = 2>
class Tree {
public:
    Tree();

    void add_root(Node<T>& root_node);
    void add_sub_node(Node<T>& parent_node, Node<T>& child_node);

    void traverseBFS(const std::function<void(const T&)>& visit);
    void traverseDFS(const std::function<void(const T&)>& visit);
    void printTreeGUI() const;
    void drawNode(QGraphicsScene& scene, Node<T>* node, int x, int y, int hGap, int vGap, int depth = 0) const;


    // Pre-order Iterator
    class PreOrderIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        PreOrderIterator(pointer ptr) {
            if (ptr) stack.push(ptr);
        }

        reference operator*() const {
            return *stack.top();
        }

        pointer operator->() {
            return stack.top();
        }

        PreOrderIterator& operator++() {
            pointer node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                if (*it) stack.push(*it);
            }
            return *this;
        }

        PreOrderIterator operator++(int) {
            PreOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const PreOrderIterator& a, const PreOrderIterator& b) {
            return a.stack == b.stack;
        }

        friend bool operator!=(const PreOrderIterator& a, const PreOrderIterator& b) {
            return !(a == b);
        }

    private:
        std::stack<pointer> stack;
    };

    // Post-order Iterator
    class PostOrderIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        PostOrderIterator(pointer ptr) {
            if (ptr) {
                fillStack(ptr);
            }
        }

        reference operator*() const {
            return *stack.top();
        }

        pointer operator->() {
            return stack.top();
        }

        PostOrderIterator& operator++() {
            if (!stack.empty()) {
                stack.pop();
            }
            return *this;
        }

        PostOrderIterator operator++(int) {
            PostOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const PostOrderIterator& a, const PostOrderIterator& b) {
            return a.stack == b.stack;
        }

        friend bool operator!=(const PostOrderIterator& a, const PostOrderIterator& b) {
            return !(a == b);
        }

    private:
        std::stack<pointer> stack;

        void fillStack(pointer node) {
            std::stack<pointer> tempStack;
            tempStack.push(node);
            while (!tempStack.empty()) {
                pointer n = tempStack.top();
                tempStack.pop();
                stack.push(n);
                for (auto it = n->children.begin(); it != n->children.end(); ++it) {
                    if (*it) tempStack.push(*it);
                }
            }
        }
    };
// In-order Iterator (generalized as DFS for n-ary trees)
class InOrderIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Node<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = Node<T>*;
    using reference = Node<T>&;

    InOrderIterator(pointer root) {
        if (root) {
            fillStack(root);
            advance();
        }
    }

    reference operator*() const {
        return *current;
    }

    pointer operator->() {
        return current;
    }

    InOrderIterator& operator++() {
        advance();
        return *this;
    }

    InOrderIterator operator++(int) {
        InOrderIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const InOrderIterator& a, const InOrderIterator& b) {
        return a.current == b.current;
    }

    friend bool operator!=(const InOrderIterator& a, const InOrderIterator& b) {
        return !(a == b);
    }

private:
    std::stack<pointer> stack;
    pointer current = nullptr;

    void fillStack(pointer node) {
        while (node) {
            stack.push(node);
            if (!node->children.empty()) {
                node = node->children[0];
            } else {
                break;
            }
        }
    }

    void advance() {
        if (stack.empty()) {
            current = nullptr;
            return;
        }

        current = stack.top();
        stack.pop();

        if (current && current->children.size() > 1) {
            for (size_t i = 1; i < current->children.size(); ++i) {
                fillStack(current->children[i]);
            }
        }
    }
};


    // BFS Iterator
    class BFSIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        BFSIterator(pointer ptr) {
            if (ptr) queue.push(ptr);
        }

        reference operator*() const {
            return *queue.front();
        }

        pointer operator->() {
            return queue.front();
        }

        BFSIterator& operator++() {
            pointer node = queue.front();
            queue.pop();
            for (auto child : node->children) {
                if (child) queue.push(child);
            }
            return *this;
        }

        BFSIterator operator++(int) {
            BFSIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const BFSIterator& a, const BFSIterator& b) {
            return a.queue == b.queue;
        }

        friend bool operator!=(const BFSIterator& a, const BFSIterator& b) {
            return !(a == b);
        }

    private:
        std::queue<pointer> queue;
    };

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    BFSIterator begin() {
        return begin_bfs_scan();
    }

    BFSIterator end() {
        return end_bfs_scan();
    }

private:
    Node<T>* root;
};

template <typename T, std::size_t N>
Tree<T, N>::Tree() : root(nullptr) {}

template <typename T, std::size_t N>
void Tree<T, N>::add_root(Node<T>& root_node) {
    root = &root_node;
}

template <typename T, std::size_t N>
void Tree<T, N>::add_sub_node(Node<T>& parent_node, Node<T>& child_node) {
    if (!root) {
        throw std::runtime_error("Tree is empty. Add root first.");
    }
    parent_node.addChild(&child_node);
}

template <typename T, std::size_t N>
void Tree<T, N>::traverseBFS(const std::function<void(const T&)>& visit) {
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

template <typename T, std::size_t N>
void Tree<T, N>::traverseDFS(const std::function<void(const T&)>& visit) {
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
template <typename T, std::size_t N>
void Tree<T, N>::printTreeGUI() const {
    int argc = 0;
    char *argv[] = { (char*)"" };
    QApplication app(argc, argv);

    QGraphicsScene scene;

    int startX = 750;
    int startY = 50;
    int hGap = 200 * (N - 1);
    int vGap = 100;

    drawNode(scene, root, startX, startY, hGap, vGap);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QLinearGradient gradient(0, 0, 0, 800);
    gradient.setColorAt(0, QColor(60, 60, 60));
    gradient.setColorAt(1, QColor(30, 30, 30));
    view.setBackgroundBrush(gradient);

    view.setWindowTitle("Tree Visualization");
    view.setFixedSize(1600, 900);
    scene.setSceneRect(0, 0, 1500, 800);

    view.show();

    app.exec();
}

template <typename T, std::size_t N>
void Tree<T, N>::drawNode(QGraphicsScene& scene, Node<T>* node, int x, int y, int hGap, int vGap, int depth) const {
    if (!node) return;

    std::ostringstream oss;
    oss << node->key;
    QGraphicsTextItem* textItem = scene.addText(QString::fromStdString(oss.str()));
    textItem->setDefaultTextColor(Qt::white);
    textItem->setZValue(1);

    QColor borderColor, edgeColor;
    edgeColor = borderColor = QColor(29, 35, 189);

    QRectF rect = textItem->boundingRect();
    QColor backgroundColor(85, 85, 90);
    QGraphicsRectItem* rectItem = scene.addRect(rect.adjusted(-25, -10, 25, 10), QPen(borderColor, 2), QBrush(backgroundColor));
    rectItem->setPos(x - rect.width() / 2 - 25, y - rect.height() / 2 - 10);

    int rectCenterX = x - rect.width() / 2 - 25;
    int rectCenterY = y - rect.height() / 2 - 10;
    textItem->setPos(rectCenterX + rect.width() / 2 - textItem->boundingRect().width() / 2,
                     rectCenterY + rect.height() / 2 - textItem->boundingRect().height() / 2);

    int screen_padding = 10;
    int childY = y + vGap;
    int numChildren = node->children.size();
    int childXLow = 0;
    int childXHigh = x - screen_padding + hGap;
    if (numChildren > 0) {
        int totalWidth;
        if (numChildren % 2 != 0) {
            totalWidth = ((numChildren - 1) * hGap) / 2;
        } else {
            totalWidth = (numChildren * hGap) / 2;
        }
        childXLow = x - totalWidth - screen_padding;
    }

    int numOfChild = 0;
    for (Node<T>* child : node->children) {
        if (child) {
            if (numOfChild < numChildren / 2 || N == 1) {
                scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                              childXLow - rect.width(), childY - rect.height() / 2 - screen_padding, QPen(edgeColor, 2));
                drawNode(scene, child, childXLow, childY, hGap - hGap / 3, vGap, depth + 1);
                childXLow += hGap;
            } else if (numOfChild >= numChildren / 2) {
                if (!(numChildren % 2 != 0 && numOfChild == numChildren / 2) || numChildren == 1) {
                    scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                                  childXHigh + rect.width() / 2, childY - rect.height() / 2 - screen_padding, QPen(edgeColor, 2));
                    drawNode(scene, child, childXHigh, childY, hGap - hGap / 3, vGap, depth + 1);
                    childXHigh += hGap;
                } else {
                    scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                                  x - screen_padding - rect.width() / 2, childY - rect.height() / 2 - screen_padding, QPen(edgeColor, 2));
                    drawNode(scene, child, x, childY, hGap - hGap / 3, vGap, depth + 1);
                }
            }
        }
        numOfChild++;
    }
}
#endif