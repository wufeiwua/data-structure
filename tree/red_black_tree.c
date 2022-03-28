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

PtrNode FixAfterInsertion(PtrNode node);
PtrNode FixAfterDeletion(PtrNode node);
PtrNode LeftRoate(PtrNode node);
PtrNode RightRoate(PtrNode node);
PtrNode NewNode(ElementType value, PtrNode parent);

PtrNode Insert(ElementType value, PtrNode root)
{
    PtrNode cur = root;
    PtrNode parent = NULL;
    // 查找父节点
    while (cur != NULL)
    {
        parent = cur;
        if (value < cur->value)
        {
            cur = cur->left;
        }
        else if (value > cur->value)
        {
            cur = cur->right;
        }
    }

    cur = NewNode(value, parent);
    // // 从当前节点自底向上平衡
    while (cur)
    {
        cur = FixAfterInsertion(cur);
        if (cur->parent == NULL)
        {
            cur->color = BLACK;
            root = cur;
            break;
        }
    }
    return root;
}

PtrNode Delete(ElementType value);
PtrNode Get(ElementType value);

PtrNode FixAfterInsertion(PtrNode node)
{
    if (node == NULL)
    {
        return node;
    }
    // 当前节点如果是黑色，直接处理父亲节点
    if (node->color == BLACK)
    {
        return node->parent;
    }

    PtrNode parent = node->parent;

    // case1: 父节点为空，此节点是根节点
    if (parent == NULL)
    {
        node->color = BLACK;
        return node;
    }
    // case2: 父亲是黑色节点，直接插入
    else if (parent->color == BLACK)
    {
        return parent;
    }

    PtrNode gradpa = parent->parent;
    if (gradpa)
    {
        // case3: 叔叔和父亲存在且都为红色。变色，父亲和叔叔变为黑色。祖父变为红色
        if (gradpa->left != NULL && gradpa->left->color == RED && gradpa->right && gradpa->right->color == RED)
        {
            gradpa->color = RED;
            gradpa->left->color = gradpa->right->color = BLACK;
            return gradpa;
        }
        else if (gradpa->left == parent && parent->left == node)
        {
            node = RightRoate(gradpa);
        }
        else if (gradpa->right == parent && parent->right == node)
        {
            node = LeftRoate(gradpa);
        }
        else if (gradpa->left == parent && parent->right == node)
        {
            gradpa->left = LeftRoate(gradpa->left);
            node = RightRoate(gradpa);
        }
        else if (gradpa->right == parent && parent->left == node)
        {
            gradpa->right = RightRoate(gradpa->right);
            node = LeftRoate(gradpa);
        }

        // 旋转过后，修改子树新根父节点的左右子树
        if (node->parent)
        {
            if (node->value > node->parent->value)
            {
                node->parent->right = node;
            }
            else
            {
                node->parent->left = node;
            }
        }
    }
    else
    {
        return parent;
    }
    return node;
}

PtrNode NewNode(ElementType value, PtrNode parent)
{
    PtrNode node = (PtrNode)malloc(sizeof(Node));
    node->color = RED;
    node->left = node->right = NULL;
    node->parent = parent;
    node->value = value;
    if (parent && value > parent->value)
    {
        parent->right = node;
    }
    else if (parent && value < parent->value)
    {
        parent->left = node;
    }
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
