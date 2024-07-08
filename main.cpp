#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

int main() {
    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
   
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value()<<",";
    }
    cout << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() <<",";
    }
    cout << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() <<",";
    }
    cout << endl;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << node->get_value() <<",";
    }
    cout << endl;

    for (auto node : tree) {
        cout << node.get_value() <<",";
    }
    cout << endl;

    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // Complex number tree
    Node<Complex> complex_root = Node<Complex>(Complex(1.1, 2.2));
    Tree<Complex> complex_tree; // Binary tree that contains complex numbers.
    complex_tree.add_root(complex_root);
    Node<Complex> c1 = Node<Complex>(Complex(1.2, 2.3));
    Node<Complex> c2 = Node<Complex>(Complex(1.3, 2.4));
    Node<Complex> c3 = Node<Complex>(Complex(1.4, 2.5));
    Node<Complex> c4 = Node<Complex>(Complex(1.5, 2.6));
    Node<Complex> c5 = Node<Complex>(Complex(1.6, 2.7));

    complex_tree.add_sub_node(complex_root, c1);
    complex_tree.add_sub_node(complex_root, c2);
    complex_tree.add_sub_node(c1, c3);
    complex_tree.add_sub_node(c1, c4);
    complex_tree.add_sub_node(c2, c5);

    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
        cout << node->get_value() << ",";
    }
    cout << endl;

    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node) {
        cout << node->get_value() << ",";
    }
    cout << endl;

    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        cout << node->get_value() << ",";
    }
    cout << endl;

    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << ",";
    }
    cout << endl;

    for (auto node : complex_tree) {
        cout << node.get_value() << ",";
    }
    cout << endl;
}
