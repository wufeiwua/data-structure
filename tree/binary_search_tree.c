/* 二叉查找树 */
/* 性质：左节点永远比右节点的值小 */

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"
PtrNode FindMin(PtrNode rootNode);
PtrNode FindMax(PtrNode rootNode);

PtrTree MakeTree()
{
    PtrTree tree = (PtrTree)malloc(sizeof(BinaryTree));
    if (tree == NULL)
    {
        printf("cannot make a tree, out of space\n");
    }
    return tree;
}

void MakeEmpty();

PtrNode GetRoot(PtrTree tree)
{
    return tree->root;
}

PtrNode Find(Element element, PtrNode rootNode)
{
    PtrNode root = rootNode;
    if (root == NULL)
    {
        return NULL;
    }
    if (element < root->item)
    {
        return Find(element, root->left);
    }
    else if (element > root->item)
    {
        return Find(element, root->right);
    }
    else
    {
        return root;
    }
}

PtrNode FindMin(PtrNode rootNode)
{
    PtrNode root = rootNode;
    while (root != NULL)
    {
        root = root->left;
    }
    return root;
}

PtrNode FindMax(PtrNode rootNode)
{
    PtrNode root = rootNode;
    while (root != NULL)
    {
        root = root->right;
    }
    return root;
}

PtrNode Insert(Element element, PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        rootNode = (PtrNode)malloc(sizeof(TreeNode));
        rootNode->left = rootNode->right = NULL;
        rootNode->item = element;
    }
    if (element < rootNode->item)
    {
        rootNode->left = Insert(element, rootNode->left);
    }
    else if (element > rootNode->item)
    {
        rootNode->right = Insert(element, rootNode->right);
    }
    return rootNode;
}

int Delete(Element element, PtrNode rootNode);