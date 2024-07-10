//asaf0604@gmail.com  325362457
#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <functional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <iterator>
#include <QApplication>
#include <QMainWindow>
#include <QTreeWidget>
#include <QVBoxLayout>

template <typename T, std::size_t N = 2>
class Tree
{
public:
    Tree();
    Node<T> *get_root() const;
    void add_root(Node<T> &root_node);
    void add_sub_node(Node<T> &parent_node, Node<T> &child_node);

    void traverseBFS(const std::function<void(const T &)> &visit);
    void traverseDFS(const std::function<void(const T &)> &visit);

    class PreOrderIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T> *;
        using reference = Node<T> &;

        PreOrderIterator(pointer ptr)
        {
            if (ptr)
                stack.push(ptr);
        }

        reference operator*() const
        {
            return *stack.top();
        }

        pointer operator->()
        {
            return stack.top();
        }

        PreOrderIterator &operator++()
        {
            pointer node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
            {
                if (*it)
                    stack.push(*it);
            }
            return *this;
        }

        PreOrderIterator operator++(int)
        {
            PreOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const PreOrderIterator &a, const PreOrderIterator &b)
        {
            return a.stack == b.stack;
        }

        friend bool operator!=(const PreOrderIterator &a, const PreOrderIterator &b)
        {
            return !(a == b);
        }

    private:
        std::stack<pointer> stack;
    };

    class PostOrderIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T> *;
        using reference = Node<T> &;

        PostOrderIterator(pointer ptr)
        {
            if (ptr)
            {
                fillStack(ptr);
            }
        }

        reference operator*() const
        {
            return *stack.top();
        }

        pointer operator->()
        {
            return stack.top();
        }

        PostOrderIterator &operator++()
        {
            if (!stack.empty())
            {
                stack.pop();
            }
            return *this;
        }

        PostOrderIterator operator++(int)
        {
            PostOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const PostOrderIterator &a, const PostOrderIterator &b)
        {
            return a.stack == b.stack;
        }

        friend bool operator!=(const PostOrderIterator &a, const PostOrderIterator &b)
        {
            return !(a == b);
        }

    private:
        std::stack<pointer> stack;

        void fillStack(pointer node)
        {
            std::stack<pointer> tempStack;
            tempStack.push(node);
            while (!tempStack.empty())
            {
                pointer n = tempStack.top();
                tempStack.pop();
                stack.push(n);
                for (auto it = n->children.begin(); it != n->children.end(); ++it)
                {
                    if (*it)
                        tempStack.push(*it);
                }
            }
        }
    };

    class InOrderIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T> *;
        using reference = Node<T> &;

        InOrderIterator(pointer root)
        {
            if (root)
            {
                fillStack(root);
                advance();
            }
        }

        reference operator*() const
        {
            return *current;
        }

        pointer operator->()
        {
            return current;
        }

        InOrderIterator &operator++()
        {
            advance();
            return *this;
        }

        InOrderIterator operator++(int)
        {
            InOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const InOrderIterator &a, const InOrderIterator &b)
        {
            return a.current == b.current;
        }

        friend bool operator!=(const InOrderIterator &a, const InOrderIterator &b)
        {
            return !(a == b);
        }

    private:
        std::stack<pointer> stack;
        pointer current = nullptr;

        void fillStack(pointer node)
        {
            while (node)
            {
                stack.push(node);
                if (!node->children.empty())
                {
                    node = node->children[0];
                }
                else
                {
                    break;
                }
            }
        }

        void advance()
        {
            if (stack.empty())
            {
                current = nullptr;
                return;
            }

            current = stack.top();
            stack.pop();

            if (current && current->children.size() > 1)
            {
                for (size_t i = 1; i < current->children.size(); ++i)
                {
                    fillStack(current->children[i]);
                }
            }
        }
    };

    class BFSIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T> *;
        using reference = Node<T> &;

        BFSIterator(pointer ptr)
        {
            if (ptr)
                queue.push(ptr);
        }

        reference operator*() const
        {
            return *queue.front();
        }

        pointer operator->()
        {
            return queue.front();
        }

        BFSIterator &operator++()
        {
            pointer node = queue.front();
            queue.pop();
            for (auto child : node->children)
            {
                if (child)
                    queue.push(child);
            }
            return *this;
        }

        BFSIterator operator++(int)
        {
            BFSIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const BFSIterator &a, const BFSIterator &b)
        {
            return a.queue == b.queue;
        }

        friend bool operator!=(const BFSIterator &a, const BFSIterator &b)
        {
            return !(a == b);
        }

    private:
        std::queue<pointer> queue;
    };

    PreOrderIterator begin_pre_order()
    {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order()
    {
        return PreOrderIterator(nullptr);
    }

    PostOrderIterator begin_post_order()
    {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order()
    {
        return PostOrderIterator(nullptr);
    }

    InOrderIterator begin_in_order()
    {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order()
    {
        return InOrderIterator(nullptr);
    }

    BFSIterator begin_bfs_scan()
    {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan()
    {
        return BFSIterator(nullptr);
    }

    BFSIterator begin()
    {
        return begin_bfs_scan();
    }

    BFSIterator end()
    {
        return end_bfs_scan();
    }

    void display(int argc, char *argv[]);

private:
    Node<T> *root;

    template <typename U>
    void addChildren(QTreeWidgetItem *parentItem, Node<U> *node);
};

template <typename T, std::size_t N>
Tree<T, N>::Tree() : root(nullptr) {}

template <typename T, std::size_t N>
void Tree<T, N>::add_root(Node<T> &root_node)
{
    root = &root_node;
}

template <typename T, std::size_t N>
void Tree<T, N>::add_sub_node(Node<T> &parent_node, Node<T> &child_node)
{
    if (!root)
    {
        throw std::runtime_error("Tree is empty. Add root first.");
    }
    parent_node.addChild(&child_node);
}

template <typename T, std::size_t N>
void Tree<T, N>::traverseBFS(const std::function<void(const T &)> &visit)
{
    if (!root)
        return;

    std::queue<Node<T> *> nodes;
    nodes.push(root);

    while (!nodes.empty())
    {
        Node<T> *node = nodes.front();
        nodes.pop();
        visit(node->key);

        for (Node<T> *child : node->children)
        {
            if (child)
            {
                nodes.push(child);
            }
        }
    }
}

template <typename T, std::size_t N>
void Tree<T, N>::traverseDFS(const std::function<void(const T &)> &visit)
{
    if (!root)
        return;

    std::stack<Node<T> *> nodes;
    nodes.push(root);

    while (!nodes.empty())
    {
        Node<T> *node = nodes.top();
        nodes.pop();
        visit(node->key);

        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
        {
            if (*it)
            {
                nodes.push(*it);
            }
        }
    }
}

template <typename T, std::size_t N>
void Tree<T, N>::display(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    QTreeWidget *treeWidget = new QTreeWidget(&mainWindow);
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel("Tree");

    if (root)
    {
        QTreeWidgetItem *rootItem = new QTreeWidgetItem(treeWidget);
        rootItem->setText(0, QString::number(root->key));
        treeWidget->addTopLevelItem(rootItem);
        addChildren(rootItem, root);
    }

    mainWindow.setCentralWidget(treeWidget);
    mainWindow.resize(400, 300);
    mainWindow.show();
    app.exec();
}
template <typename T, std::size_t N>
Node<T> *Tree<T, N>::get_root() const
{
    return root;
}
template <typename T, std::size_t N>
template <typename U>
void Tree<T, N>::addChildren(QTreeWidgetItem *parentItem, Node<U> *node)
{
    for (auto child : node->children)
    {
        if (child)
        {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, QString::number(child->key));
            parentItem->addChild(childItem);
            addChildren(childItem, child);
        }
    }
}

#endif