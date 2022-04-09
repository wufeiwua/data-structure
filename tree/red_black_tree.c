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
void LeftRoate(PtrNode node, PtrRoot root);
void RightRoate(PtrNode node, PtrRoot root);
PtrNode NewNode(ElementType value, PtrNode parent);
PtrNode FindMin(PtrNode node);

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
    if (parent == NULL)
    {
        // 根节点
        cur->color = BLACK;
        *root = cur;
        return;
    }
    // 从当前节点自底向上修正红黑树
    FixAfterInsertion(cur, root);
}

void Delete(ElementType value, PtrRoot root)
{
    PtrNode node = Get(value, root);
    if (node == NULL)
    {
        // 该节点不存在
        return;
    }

    // 转为删除一个孩子的情况
    if (node->left && node->right)
    {
        // 找到右子树的最小值，此节点必定没有左子树
        PtrNode min = FindMin(node->right);
        node->value = min->value;
        node->color = min->color;
        node = min;
    }

    // 待删除节点只有一个子节点，或者没有儿子
    PtrNode replacement = node->left ? node->left : node->right;
    // 有一个儿子
    if (replacement)
    {
        replacement->parent = node->parent;
        // 待删除节点是根
        if (node->parent == NULL)
        {
            *root = replacement;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = replacement;
        }
        else
        {
            node->parent->right = replacement;
        }

        // 删除当前节点
        node->parent = node->left = node->right = NULL;
        if (node->color == BLACK)
        {
            // node 被删除，以被替代的节点为起点
            FixAfterDeletion(replacement, root);
        }
        free(node);
    }
    // 没有儿子，且为根
    else if (node->parent == NULL)
    {
        free(node);
        *root = NULL;
    }
    // 没有儿子，不为根
    else
    {
        // 黑色需要先修正
        if (node->color == BLACK)
        {
            FixAfterDeletion(node, root);
        }

        // 删除该节点
        if (node == node->parent->left)
        {
            node->parent->left = NULL;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = NULL;
        }
        node->parent = NULL;
        free(node);
    }
}
PtrNode Get(ElementType value, PtrRoot root)
{
    PtrNode cur = *root;
    while (cur != NULL)
    {
        if (value < cur->value)
        {
            cur = cur->left;
        }
        else if (value > cur->value)
        {
            cur = cur->right;
        }
        else
        {
            break;
        }
    }
    return cur;
}

PtrNode FindMin(PtrNode node)
{
    while (node != NULL && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

/*
0. 此节点是根（没有父亲）： 变色（变为黑色）
1. 父亲是黑色： 直接插入
2. 父亲是红色：
     1. 叔叔是黑色，或者没有叔叔： 旋转（单旋或者双旋）+变色（子树的根为黑色，子节点为红色）
     2. 叔叔是红色： 变色 （叔叔和父亲变为黑色，祖父变为红色），然后以祖父为新的节点，继续向上平衡

 */
void FixAfterInsertion(PtrNode node, PtrRoot root)
{
    // 父亲是红色节点才需要修正，否则直接插入。root 肯定是 黑色
    while (node && node != (*root) && node->parent && node->parent->color == RED)
    {
        // 父亲是左子树
        if (node->parent == node->parent->parent->left)
        {
            // 叔叔存在且是红色
            PtrNode uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                node->parent->parent->color = RED;
                node->parent->color = uncle->color = BLACK;
                // 以祖父为新节点，继续向上
                node = node->parent->parent;
            }
            else
            {
                if (node->parent->right == node)
                {
                    // 以父节点为根旋转
                    node = node->parent;
                    LeftRoate(node, root);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RightRoate(node->parent->parent, root);
            }
        }
        // 父亲右子树
        else
        {
            // 叔叔存在且是红色
            PtrNode uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                node->parent->parent->color = RED;
                node->parent->color = uncle->color = BLACK;
                // 以祖父为新节点，继续向上
                node = node->parent->parent;
            }
            else
            {
                if (node->parent->left == node)
                {
                    node = node->parent;
                    RightRoate(node->parent, root);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                LeftRoate(node->parent->parent, root);
            }
        }
    }
    (*root)->color = BLACK;
}

/*
 */
void FixAfterDeletion(PtrNode node, PtrRoot root)
{
    // while (node != *root && node->color == BLACK)
    // {
    //     if (node == node->parent->left)
    //     {
    //         PtrNode bro = node->parent->right;
    //         if (bro && bro->color == RED)
    //         {
    //             bro->color = BLACK;
    //             bro->parent->color = RED;
    //             node = LeftRoate(node->parent);
    //             bro = node->parent->right;
    //         }
    //     }
    //     else
    //     {
    //     }
    // }
    // node->color = BLACK;
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

void LeftRoate(PtrNode node, PtrRoot root)
{
    PtrNode newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    // reset parent
    newRoot->parent = node->parent;
    node->parent = newRoot;
    if (node->right)
    {
        node->right->parent = node;
    }

    // 旋转过后，修改子树新根父节点的左右子树
    if (newRoot->parent)
    {
        if (newRoot->parent->left == node)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
    else
    {
        *root = newRoot;
    }
}

void RightRoate(PtrNode node, PtrRoot root)
{
    PtrNode newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    // reset parent
    newRoot->parent = node->parent;
    node->parent = newRoot;
    if (node->left)
    {
        node->left->parent = node;
    }

    // 旋转过后，修改子树新根父节点的左右子树
    if (newRoot->parent)
    {
        if (newRoot->parent->left == node)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;
    }
    else
    {
        *root = newRoot;
    }
}
