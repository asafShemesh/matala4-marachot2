#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

template <typename T, std::size_t N = 2>
class TreeWidget : public QWidget
{
public:
    explicit TreeWidget(QWidget *parent = nullptr) : QWidget(parent), tree(nullptr)
    {
        setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window, Qt::black);
        setPalette(palette);
    }

    void setTree(Tree<T, N> *tree)
    {
        this->tree = tree;
        update(); // Request a repaint
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        if (tree && tree->get_root())
        {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            drawNode(&painter, tree->get_root(), width() / 2, 40, width() / 4);
        }
    }

private:
    Tree<T, N> *tree;

    void drawNode(QPainter *painter, Node<T> *node, int x, int y, int xOffset)
    {
        if (!node)
            return;

        static const int RADIUS = 33;
        painter->setPen(Qt::red);
        painter->setBrush(Qt::green);

        // Draw circle
        painter->drawEllipse(x - RADIUS, y - RADIUS, 2 * RADIUS, 2 * RADIUS);

        // Draw text
        QRect rect(x - RADIUS, y - RADIUS, 2 * RADIUS, 2 * RADIUS);
        if constexpr (std::is_same<T, Complex>::value)
        {
            painter->drawText(rect, Qt::AlignCenter, node->key.toString());
        }
        else
        {
            painter->drawText(rect, Qt::AlignCenter, QString::number(node->key));
        }

        int childY = y + 70;                             // Increased the vertical distance between nodes
        std::size_t numChildren = node->children.size(); // Use std::size_t for consistency

        for (std::size_t i = 0; i < numChildren; ++i)
        {
            Node<T> *child = node->children[i];
            if (child)
            {
                int childX = x - xOffset + (numChildren > 1 ? (2 * i * xOffset) / (numChildren - 1) : 0);

                // Draw line to child
                painter->drawLine(x, y + RADIUS, childX, childY - RADIUS);

                // Recursively draw child nodes
                drawNode(painter, child, childX, childY, xOffset / 2);
            }
        }
    }
};

#endif // TREEWIDGET_HPP
