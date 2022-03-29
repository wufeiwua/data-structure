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
void LeftRoate(PtrNode node);
void RightRoate(PtrNode node);
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
    while (node != NULL)
    {
        PtrNode parent = node->parent;
        // case1: 父节点为空，此节点是根节点
        if (parent == NULL)
        {
            node->color = BLACK;
            *root = node;
            return;
        }
        // 父节点为红色
        else if (parent->color == RED)
        {
            PtrNode gradpa = parent->parent;
            // 左子树
            if (parent == gradpa->left)
            {
                // case3: 叔叔存在且为红色
                if (gradpa->right && gradpa->right->color == RED)
                {
                    gradpa->color = RED;
                    gradpa->left->color = gradpa->right->color = BLACK;
                    // 以祖父为新节点，继续向上
                    node = gradpa;
                }
                // case4: 父亲是左子树，右旋
                else
                {
                    if (parent->right == node)
                    {
                        node = node->parent;
                        LeftRoate(parent);
                    }
                    RightRoate(gradpa);
                }
            }
            // 右子树
            else
            {
                // case3: 叔叔存在且为红色
                if (gradpa->left && gradpa->left->color == RED)
                {
                    gradpa->color = RED;
                    gradpa->left->color = gradpa->right->color = BLACK;
                    // 以祖父为新节点，继续向上
                    node = gradpa;
                }
                // case5: 父亲是右子树，左旋
                else
                {
                    if (parent->left == node)
                    {
                        node = node->parent;
                        RightRoate(parent);
                    }
                    LeftRoate(gradpa);
                }
            }
        }
        else
        {
            return;
        }
    }
    if (*root)
    {
        (*root)->color = BLACK;
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

void LeftRoate(PtrNode node)
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
            node->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
}

void RightRoate(PtrNode node)
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
            node->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
}
