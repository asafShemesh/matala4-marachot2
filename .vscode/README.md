asaf0604@gmail.com  325362457
# Matala4 Marachot2

## Overview

This project is a C++ application that demonstrates the implementation and visualization of a tree data structure. The tree can contain elements of various types, including custom `Complex` numbers, and supports multiple traversal methods. The application uses the Qt library for GUI representation, allowing users to visualize the tree structure interactively.

## Features

- **Tree Data Structure**: Supports generic tree structures with customizable node types and branching factors
- **Complex Number Handling**: Custom `Complex` class to handle complex numbers within the tree.
- **GUI Visualization**: Visual representation of the tree using the Qt framework.
- **Multiple Traversal Methods**: Supports pre-order, post-order, in-order, and breadth-first search (BFS) traversals.


## Usage

- **Complex Class (complex.hpp)**: Handles complex numbers with various operations.
- **Node Class (node.hpp)**: Template class for tree nodes.
- **Tree Class (tree.hpp)**: Template class for managing the tree data structure.
- **TreeWidget Class (TreeWidget.hpp)**: Visualizes the tree structure using Qt.
- **Main Application (main.cpp)**: Entry point of the application.

### Node Class (node.hpp)

#### Functions

- **Node<T>()**: Constructor to initialize a node.
- **Node<T>(T value)**: Constructor to initialize a node with a value.
- **T get_value() const**: Returns the value of the node.
- **void set_value(T value)**: Sets the value of the node.

### Tree Class (tree.hpp)

#### Functions

- **Tree()**: Constructor to initialize an empty tree.
- **void add_root(Node<T>& root_node)**: Sets the root of the tree.
- **void add_sub_node(Node<T>& parent_node, Node<T>& child_node)**: Adds a child node to a specified parent node.
- **void traverseBFS(const std::function<void(const T&)>& visit)**: Performs a Breadth-First Search traversal of the tree and applies the provided function `visit` to each node.
- **void traverseDFS(const std::function<void(const T&)>& visit)**: Performs a Depth-First Search traversal of the tree and applies the provided function `visit` to each node.

### Iterators

#### PreOrderIterator

- **PreOrderIterator(pointer ptr)**: Initializes the iterator.
- **reference operator*() const**: Returns the reference to the node pointed by the iterator.
- **pointer operator->()**: Returns the pointer to the node.
- **PreOrderIterator& operator++()**: Prefix increment operator.
- **PreOrderIterator operator++(int)**: Postfix increment operator.
- **friend bool operator==(const PreOrderIterator& a, const PreOrderIterator& b)**: Equality comparison.
- **friend bool operator!=(const PreOrderIterator& a, const PreOrderIterator& b)**: Inequality comparison.

#### PostOrderIterator

(Note: You may want to complete the description for `PostOrderIterator` based on its actual implementation.)

### Complex Class (complex.hpp)

#### Functions

- **Complex()**: Constructor to initialize a complex number.
- **Complex(double real, double imag)**: Constructor to initialize a complex number with given real and imaginary parts.
- **double real() const**: Returns the real part of the complex number.
- **double imag() const**: Returns the imaginary part of the complex number.
- **void set_real(double real)**: Sets the real part of the complex number.
- **void set_imag(double imag)**: Sets the imaginary part of the complex number.
- **Complex operator+(const Complex& other) const**: Adds two complex numbers.
- **Complex operator-(const Complex& other) const**: Subtracts two complex numbers.
- **Complex operator*(const Complex& other) const**: Multiplies two complex numbers.
- **Complex operator/(const Complex& other) const**: Divides two complex numbers.
- **bool operator==(const Complex& other) const**: Checks equality of two complex numbers.
- **bool operator!=(const Complex& other) const**: Checks inequality of two complex numbers.

### TreeWidget Class (TreeWidget.hpp)

- **TreeWidget(QWidget* parent = nullptr)**: Constructor to initialize the TreeWidget with an optional parent.
- **void setTree(const Tree<T>& tree)**: Sets the tree to be visualized.
- **void updateVisualization()**: Updates the visualization of the tree.

## Main Application (main.cpp)

### Overview

The main application demonstrates the usage of the tree and complex number classes. It creates instances of these classes, performs various operations, and visualizes the tree structure using the TreeWidget class.

### Usage

1. **Initialize the Tree**: Create instances of the `Node` and `Tree` classes and set up the tree structure.
2. **Initialize the Complex Numbers**: Create instances of the `Complex` class and perform operations.
3. **Visualize the Tree**: Use the `TreeWidget` class to visualize the tree structure.
4. **Run the Application**: Build and run the application to see the tree visualization and complex number operations in action.

commands:
make all
make clean
./tree
./test