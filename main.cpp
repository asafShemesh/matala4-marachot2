#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include "TreeWidget.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Tree Visualization");

    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *centralWidget = new QWidget(&mainWindow);

    // Double Tree Visualization
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

    cout << "Double Tree Traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->key << ",";
    }
    cout << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->key << ",";
    }
    cout << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->key << ",";
    }
    cout << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->key << ",";
    }
    cout << endl;

    TreeWidget<double> *doubleTreeWidget = new TreeWidget<double>();
    doubleTreeWidget->setTree(&tree);
    layout->addWidget(doubleTreeWidget);

    // Complex Tree Visualization
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

    cout << "Complex Tree Traversal:" << endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node)
    {
        cout << node->key.toString().toStdString() << ",";
    }
    cout << endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node)
    {
        cout << node->key.toString().toStdString() << ",";
    }
    cout << endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node)
    {
        cout << node->key.toString().toStdString() << ",";
    }
    cout << endl;
    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node)
    {
        cout << node->key.toString().toStdString() << ",";
    }
    cout << endl;

    TreeWidget<Complex> *complexTreeWidget = new TreeWidget<Complex>();
    complexTreeWidget->setTree(&complex_tree);
    layout->addWidget(complexTreeWidget);

    centralWidget->setLayout(layout);
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
