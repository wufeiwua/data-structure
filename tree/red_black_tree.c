#include <stdlib.h>
#include <stdio.h>
#include "red_black_tree.h"

/*
红黑树

1.结点是红色或黑色。

2.根结点是黑色。

3.每个叶子结点都是黑色的空结点（NIL结点）。

4 每个红色结点的两个子结点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色结点)

5.从任一结点到其每个叶子的所有路径都包含相同数目的黑色结点。

 */
typedef enum Position
{
    NONE,
    LEFT,
    RIGHT,
} Position;

PtrNode FixAfterInsertion(PtrNode node);
PtrNode FixAfterDeletion(PtrNode node);
PtrNode GetUncle(PtrNode node);
PtrNode LeftRoate(PtrNode node);
PtrNode RightRoate(PtrNode node);
PtrNode NewNode(ElementType value, PtrNode parent);

PtrNode Insert(ElementType value, PtrNode node)
{
    PtrNode cur = node;
    PtrNode parent = NULL;
    Position pos = NONE;
    // 查找父节点
    while (cur != NULL)
    {
        parent = cur;
        if (value < cur->value)
        {
            cur = cur->left;
            pos = LEFT;
        }
        else if (value > cur->value)
        {
            cur = cur->right;
            pos = RIGHT;
        }
    }

    cur = NewNode(value, parent);
    if (pos == LEFT)
    {
        parent->left = cur;
    }
    else if (pos == RIGHT)
    {
        parent->right = cur;
    }

    // // 从当前节点自底向上平衡
    // while (cur)
    // {
    //     cur = FixAfterInsertion(cur);
    //     if (cur->parent == NULL)
    //     {
    //         cur->color = BLACK;
    //         break;
    //     }
    // }
    if (node == NULL)
    {
        node = cur;
    }
    return node;
}

PtrNode Delete(ElementType value);
PtrNode Get(ElementType value);

PtrNode FixAfterInsertion(PtrNode node)
{
    if (node == NULL)
    {
        return node;
    }

    PtrNode parent = node->parent;
    PtrNode uncle = GetUncle(node);

    // case1: 父节点为空，此节点是根节点
    if (parent == NULL)
    {
        node->color = BLACK;
        return node;
    }
    // case2: 父亲是黑色节点，直接插入
    else if (node->parent && node->parent->color == BLACK)
    {
        return node->parent;
    }
    // case3: 叔叔存在且父亲和叔叔为红色。变色，父亲和叔叔变为黑色。祖父变为红色
    else if (parent && uncle && uncle->color == RED)
    {
        parent->color = uncle->color = BLACK;
        parent->parent->color = RED;
        return parent->parent;
    }
    // 此时，由于红黑树特性，该节点的祖父必定存在。case1 和 case2 已经完成了前两层的处理
    // 单边，要么，黑红红，要么，黑黑红
    else if (parent->left == node)
    {
        if (parent->parent->left == parent)
        {
            node = RightRoate(parent->parent);
        }
        else
        {
            // right node, left roate
            node = LeftRoate(node->parent);
            node = RightRoate(node->parent);
        }
    }
    else
    {
        if (parent->parent->right == parent)
        {
            node = LeftRoate(parent->parent);
        }
        else
        {
            node = RightRoate(node->parent);
            node = LeftRoate(node->parent);
        }
    }

    return node;
}

PtrNode GetUncle(PtrNode node)
{
    if (node == NULL || node->parent == NULL || node->parent->parent == NULL)
    {
        return NULL;
    }

    else if (node->parent && node->parent == node->parent->parent->left)
    {
        return node->parent->parent->right;
    }
    else
    {
        return node->parent->parent->left;
    }
}

PtrNode NewNode(ElementType value, PtrNode parent)
{
    PtrNode node = (PtrNode)malloc(sizeof(Node));
    node->color = RED;
    node->left = node->right = NULL;
    node->parent = parent;
    node->value = value;
    return node;
}

PtrNode LeftRoate(PtrNode node)
{
    PtrNode newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    // reset color
    newRoot->color = BLACK;
    node->color = RED;

    // reset parent
    newRoot->parent = node->parent;
    node->parent = newRoot;
    return newRoot;
}

PtrNode RightRoate(PtrNode node)
{
    PtrNode newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    // reset color
    node->color = RED;
    newRoot->color = BLACK;

    // reset parent
    newRoot->parent = node->parent;
    node->parent = newRoot;
    return newRoot;
}
