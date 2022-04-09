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
int IsBlack(PtrNode node);

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
        // 找到右子树的最小值，此节点必定没有左子树，只复制值，并不复制颜色
        PtrNode min = FindMin(node->right);
        node->value = min->value;
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

int IsBlack(PtrNode node)
{
    return node == NULL || node->color == BLACK;
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
    // 红色树特性：根节点外，黑色节点必有一个兄弟。否则会导致树不平衡(从任一结点到其每个叶子的所有路径都包含相同数目的黑色结点)
    while (node != *root && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            PtrNode sib = node->parent->right;

            // 如果兄弟是红色，那么父亲必定是黑色的。
            // 兄弟存在且为红色。以父节点为根做一次旋转，但是此时还不能完全修复，需要继续判断
            // 原有的兄弟变为祖父，且编程黑色。父亲变为红色，兄弟也会更新
            if (sib->color == RED)
            {
                sib->color = BLACK;
                sib->parent->color = RED;
                LeftRoate(node->parent, root);
                sib = node->parent->right;
            }

            // 兄弟为黑色，兄弟的孩子都是黑色。
            if (IsBlack(sib->left) && IsBlack(sib->right))
            {
                // 兄弟和侄子都是黑色，父亲是红色
                if (node->parent->color == RED)
                {
                    node->parent->color = BLACK;
                    sib->color = RED;
                    return;
                }

                // 父亲、兄弟、侄子都是黑色
                sib->color = RED;
                node = node->parent;
            }
            // 其中一个侄子为红色
            else
            {
                // 兄弟为黑色，且右儿子为黑色，变为右儿子为红色情况，再继续平衡
                if (sib->right == NULL || sib->right->color == BLACK)
                {
                    sib->color = RED;
                    if (sib->left)
                    {
                        sib->left->color = BLACK;
                    }
                    RightRoate(sib, root);

                    sib = node->parent->right;
                }

                // 最后一种情况，兄弟是黑色，右儿子是红色的
                sib->color = node->parent->color;
                sib->right->color = node->parent->color = BLACK;
                LeftRoate(node->parent, root);
                break;
            }
        }

        // 镜像操作
        else
        {
            PtrNode sib = node->parent->left;

            if (sib->color == RED)
            {
                sib->color = BLACK;
                sib->parent->color = RED;
                RightRoate(node->parent, root);
                sib = node->parent->left;
            }

            if (IsBlack(sib->left) && IsBlack(sib->right))
            {
                if (node->parent->color == RED)
                {
                    node->parent->color = BLACK;
                    sib->color = RED;
                    return;
                }

                sib->color = RED;
                node = node->parent;
            }
            else
            {
                if (sib->left == NULL || sib->left->color == BLACK)
                {
                    sib->color = RED;
                    if (sib->right)
                    {
                        sib->right->color = BLACK;
                    }

                    LeftRoate(sib, root);

                    sib = node->parent->left;
                }

                sib->color = node->parent->color;
                sib->left->color = node->parent->color = BLACK;
                RightRoate(node->parent, root);
                break;
            }
        }
    }
    node->color = BLACK;
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
