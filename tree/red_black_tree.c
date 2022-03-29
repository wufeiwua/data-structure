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

void FixAfterInsertion(PtrNode node, PtrRoot root);
void FixAfterDeletion(PtrNode node, PtrRoot root);
PtrNode LeftRoate(PtrNode node);
PtrNode RightRoate(PtrNode node);
PtrNode NewNode(ElementType value, PtrNode parent);

void Insert(ElementType value, PtrRoot root)
{
    PtrNode cur = *root;
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
    // 从当前节点自底向上修正红黑树
    FixAfterInsertion(cur, root);
}

void Delete(ElementType value, PtrRoot root);
PtrNode Get(ElementType value, PtrRoot root);

void FixAfterInsertion(PtrNode node, PtrRoot root)
{
    // 父亲是红色节点才需要修正，否则直接插入。root 肯定是 黑色
    while (node)
    {
        if (node->parent && node->parent->color == RED)
        {
            if (node->parent->parent->right && node->parent->parent->right->color == RED && node->parent->parent->left && node->parent->parent->left->color == RED)
            {
                node->parent->parent->color = RED;
                node->parent->parent->left->color = node->parent->parent->right->color = BLACK;
                // 以祖父为新节点，继续向上
                node = node->parent->parent;
            }
            // 父亲左子树
            else if (node->parent == node->parent->parent->left)
            {

                if (node->parent->right == node)
                {
                    // 以父节点为根旋转
                    node = node->parent;
                    node->parent->left = LeftRoate(node);
                }
                node = RightRoate(node->parent->parent);
                if (node->parent == NULL)
                {
                    node->color = BLACK;
                    *root = node;
                }
                return;
            }
            // 父亲右子树
            else
            {
                // case5: 父亲是右子树，左旋
                if (node->parent->left == node)
                {
                    node = node->parent;
                    RightRoate(node->parent);
                }
                node = LeftRoate(node->parent->parent);
                if (node->parent == NULL)
                {
                    node->color = BLACK;
                    *root = node;
                }
                return;
            }
        }
        else
        {
            if (node->parent == NULL)
            {
                node->color = BLACK;
                *root = node;
            }
            return;
        }
    }
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

    // 旋转过后，修改子树新根父节点的左右子树
    if (newRoot->parent)
    {
        if (newRoot->parent->left == node)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
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

    // 旋转过后，修改子树新根父节点的左右子树
    if (newRoot->parent)
    {
        if (newRoot->parent->left == node)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
    return newRoot;
}
