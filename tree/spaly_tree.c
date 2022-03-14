/**
 * @file spaly_tree.c
 * @author wufeiwua
 * @brief
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 *
 * 伸展树
 * 特性：当一个节点被访问后应当旋转到根节点的位置，以便下次访问的时候更快
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

PtrNode FindMin(PtrNode rootNode);
PtrNode FindMax(PtrNode rootNode);
PtrNode FindNode(int element, PtrNode rootNode);
PtrNode InsertNode(int element, PtrNode rootNode);
PtrNode DeleteNode(int element, PtrNode rootNode);
PtrNode Splay(PtrNode node);
// LL
PtrNode LLRotate(PtrNode node);
// LR
PtrNode LRRotate(PtrNode node);
// RR
PtrNode RRRotate(PtrNode node);
// RL
PtrNode RLRotate(PtrNode node);

PtrTree MakeTree()
{
    PtrTree tree = (PtrTree)malloc(sizeof(BinaryTree));
    if (tree == NULL)
    {
        printf("cannot make, out of space.\n");
    }
    return tree;
}

PtrNode MakeEmpty(PtrNode rootNode)
{
    while (rootNode != NULL)
    {
        rootNode->left = MakeEmpty(rootNode->left);
        rootNode->right = MakeEmpty(rootNode->right);
        free(rootNode);
    }
    return NULL;
}

PtrNode GetRoot(PtrTree tree)
{
    return tree->root;
}

PtrNode Find(int element, PtrTree tree)
{
    PtrNode node = FindNode(element, tree->root);

    while (node && node->parent)
    {
        node = Splay(node);
    }
    if (node)
    {
        tree->root = node;
    }
    return node;
}

PtrNode FindNode(int element, PtrNode rootNode)
{
    PtrNode root = rootNode;
    if (root == NULL)
    {
        printf("not find, root node is NULL.\n");
        return NULL;
    }
    if (element < root->item)
    {
        return FindNode(element, root->left);
    }
    else if (element > root->item)
    {
        return FindNode(element, root->right);
    }
    else
    {
        return root;
    }
}

PtrNode Insert(int element, PtrTree tree)
{
    tree->root = InsertNode(element, tree->root);
    tree->root = Find(element, tree);
    return tree->root;
}

PtrNode Delete(int element, PtrTree tree)
{
    // 先找这个元素，将其旋转到根节点，并平衡二叉树
    PtrNode root = Find(element, tree);
    if (root == NULL)
    {
        printf("cannot delete, node is NULL.\n");
        return NULL;
    }
    // 更新根节点
    tree->root = root;
    tree->root = DeleteNode(element, tree->root);
    return tree->root;
}

PtrNode InsertNode(int element, PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        rootNode = (PtrNode)malloc(sizeof(TreeNode));
        rootNode->left = rootNode->right = NULL;
        rootNode->item = element;
    }
    if (element < rootNode->item)
    {
        rootNode->left = InsertNode(element, rootNode->left);
        rootNode->left->parent = rootNode;
    }
    else if (element > rootNode->item)
    {
        rootNode->right = InsertNode(element, rootNode->right);
        rootNode->right->parent = rootNode;
    }
    return rootNode;
}

PtrNode DeleteNode(int element, PtrNode rootNode)
{

    PtrNode left = rootNode->left;
    PtrNode right = rootNode->right;
    if (left == NULL && right == NULL)
    {
        // only one
        free(rootNode);
        return NULL;
    }

    // 断开左右树
    rootNode->left = NULL;
    rootNode->right = NULL;

    PtrNode leftMax = NULL;
    if (left)
    {
        // 找左子树的最大节点（这个节点将会被旋转到左子树的根，且这个节点不会有右节点）
        left->parent = NULL;
        leftMax = FindMax(left);
        while (leftMax && leftMax->parent)
        {
            leftMax = Splay(leftMax);
        }
    }

    if (right)
    {
        right->parent = leftMax;
    }

    // 接右树
    leftMax->right = right;
    free(rootNode);

    // 也可以找右子树的最小节点（这个节点将会被旋转到右子树的根，且这个节点不会有左节点）。然后将左子树接过来

    return leftMax;
}

PtrNode Splay(PtrNode node)
{
    // zig 该节点是根节点的左子节点
    if (node->parent && node->parent->parent == NULL && node->item < node->parent->item)
    {
        return LLRotate(node->parent);
    }
    // zag 该节点是根节点的右子节点
    else if (node->parent && node->parent->parent == NULL && node->item > node->parent->item)
    {
        return RRRotate(node->parent);
    }
    // zig-zig 该节点有父亲和祖父节点，且都在左边
    else if (node->parent && node->parent->parent && node->parent->item < node->parent->parent->item && node->item < node->parent->item)
    {
        PtrNode parent = LLRotate(node->parent->parent);
        PtrNode new_node = LLRotate(parent);
        if (new_node->parent)
        {
            new_node->parent->left = new_node;
        }
        return new_node;
    }
    // zag-zag 该节点有父亲和祖父节点，且都在右边
    else if (node->parent && node->parent->parent && node->parent->item > node->parent->parent->item && node->item > node->parent->item)
    {
        PtrNode parent = RRRotate(node->parent->parent);
        PtrNode new_node = RRRotate(parent);
        if (new_node->parent)
        {
            new_node->parent->right = new_node;
        }
        return new_node;
    }
    // zig-zag  该节点有父亲和祖父节点，且父亲在祖父左边，节点在父亲右边 LR
    else if (node->parent && node->parent->parent && node->parent->item < node->parent->parent->item && node->item > node->parent->item)
    {
        return LRRotate(node->parent->parent);
    }
    // zag-zig 该节点有父亲和祖父节点，且父亲在祖父右边，节点在父亲左边 RL
    else if (node->parent && node->parent->parent && node->parent->item > node->parent->parent->item && node->item < node->parent->item)
    {
        return RLRotate(node->parent->parent);
    }
    else
    {
        // is root
        return node;
    }
}

// LL
PtrNode LLRotate(PtrNode node)
{
    PtrNode parent = node->parent;
    PtrNode new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    // 改变parent
    new_root->parent = parent;
    node->parent = new_root;
    if (node->left)
    {
        node->left->parent = node;
    }

    return new_root;
}

// RR
PtrNode RRRotate(PtrNode node)
{
    PtrNode parent = node->parent;
    PtrNode new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    new_root->parent = parent;
    node->parent = new_root;
    if (node->right)
    {
        node->right->parent = node;
    }

    return new_root;
}
// RL
PtrNode RLRotate(PtrNode node)
{
    node->right = LLRotate(node->right);
    return RRRotate(node);
}

// LR
PtrNode LRRotate(PtrNode node)
{
    node->left = RRRotate(node->left);
    return LLRotate(node);
}

PtrNode FindMin(PtrNode rootNode)
{
    PtrNode root = rootNode;
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

PtrNode FindMax(PtrNode rootNode)
{
    PtrNode root = rootNode;
    while (root != NULL && root->right != NULL)
    {
        root = root->right;
    }
    return root;
}