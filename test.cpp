//asaf0604@gmail.com  325362457
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
void print_vector(const std::vector<T> &vec)
{
    for (const auto &val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("Testing 2-ary Tree")
{
    Node<double> root_node(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    Tree<double, 2> binary_tree;
    binary_tree.add_root(root_node);
    binary_tree.add_sub_node(root_node, n1);
    binary_tree.add_sub_node(root_node, n2);
    binary_tree.add_sub_node(n1, n3);
    binary_tree.add_sub_node(n1, n4);
    binary_tree.add_sub_node(n2, n5);

    std::vector<double> bfs_result;
    for (auto it = binary_tree.begin_bfs_scan(); it != binary_tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->key);
    }
    CHECK(bfs_result == std::vector<double>{1.1, 1.2, 1.3, 1.4, 1.5, 1.6});

    std::vector<double> dfs_result;
    for (auto it = binary_tree.begin_pre_order(); it != binary_tree.end_pre_order(); ++it)
    {
        dfs_result.push_back(it->key);
    }
    CHECK(dfs_result == std::vector<double>{1.1, 1.2, 1.4, 1.5, 1.3, 1.6});

    std::vector<double> in_order_result;
    for (auto it = binary_tree.begin_in_order(); it != binary_tree.end_in_order(); ++it)
    {
        in_order_result.push_back(it->key);
    }
    CHECK(in_order_result == std::vector<double>{1.4, 1.2, 1.5, 1.1, 1.6, 1.3});

    std::vector<double> post_order_result;
    for (auto it = binary_tree.begin_post_order(); it != binary_tree.end_post_order(); ++it)
    {
        post_order_result.push_back(it->key);
    }
    CHECK(post_order_result == std::vector<double>{1.4, 1.5, 1.2, 1.6, 1.3, 1.1});
}

TEST_CASE("Testing 3-ary Tree")
{
    Node<double> root_node(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    Tree<double, 3> three_ary_tree;
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    std::vector<double> bfs_result;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->key);
    }
    CHECK(bfs_result == std::vector<double>{1.1, 1.2, 1.3, 1.4, 1.5, 1.6});

    std::vector<double> dfs_result;
    for (auto it = three_ary_tree.begin_pre_order(); it != three_ary_tree.end_pre_order(); ++it)
    {
        dfs_result.push_back(it->key);
    }
    CHECK(dfs_result == std::vector<double>{1.1, 1.2, 1.5, 1.3, 1.6, 1.4});

    std::vector<double> in_order_result;
    for (auto it = three_ary_tree.begin_in_order(); it != three_ary_tree.end_in_order(); ++it)
    {
        in_order_result.push_back(it->key);
    }
    std::cout << "3-ary Tree In-order Result: ";
    print_vector(in_order_result);
    CHECK(in_order_result == std::vector<double>{1.5, 1.2, 1.1, 1.4, 1.6, 1.3});

    std::vector<double> post_order_result;
    for (auto it = three_ary_tree.begin_post_order(); it != three_ary_tree.end_post_order(); ++it)
    {
        post_order_result.push_back(it->key);
    }
    CHECK(post_order_result == std::vector<double>{1.5, 1.2, 1.6, 1.3, 1.4, 1.1});
}
