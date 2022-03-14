/* 二叉查找树 */
/* 性质：左节点永远比右节点的值小 */

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

PtrNode FindMin(PtrNode rootNode);
PtrNode FindMax(PtrNode rootNode);
PtrNode FindNode(int element, PtrNode rootNode);
PtrNode InsertNode(int element, PtrNode rootNode);
PtrNode DeleteNode(int element, PtrNode rootNode);

PtrTree MakeTree()
{
    PtrTree tree = (PtrTree)malloc(sizeof(BinaryTree));
    if (tree == NULL)
    {
        printf("cannot make a tree, out of space\n");
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
    return FindNode(element, tree->root);
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
    if (tree == NULL)
    {
        printf("cannot insert, the tree is NULL.\n");
        return NULL;
    }
    PtrNode node = InsertNode(element, tree->root);
    if (tree->root == NULL)
    {
        tree->root = node;
    }
    return node;
}

PtrNode Delete(int element, PtrTree tree)
{
    PtrNode node = DeleteNode(element, tree->root);
    tree->root = node;
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
    }
    else if (element > rootNode->item)
    {
        rootNode->right = InsertNode(element, rootNode->right);
    }
    return rootNode;
}

/* 递归函数，就是将父节点传到下一层级，然后改变父亲的 left 指针或者 right 指针指向 */
PtrNode DeleteNode(int element, PtrNode rootNode)
{
    printf("\n\nfind node %d.\n", element);
    // 元素不存在
    if (rootNode == NULL)
    {
        printf("cannot delete, node is NULL.\n");
        return NULL;
    }
    else if (element < rootNode->item)
    {
        // 比节点元素小，说明在左节点
        // 递归, 此时 rootNode 是父亲
        printf("less than node %d, go left.\n", rootNode->item);
        rootNode->left = DeleteNode(element, rootNode->left);
    }
    else if (element > rootNode->item)
    {
        // 比节点元素大，说明在右节点
        printf("greter than node %d, go right.\n", rootNode->item);
        rootNode->right = DeleteNode(element, rootNode->right);
    }
    // 找到元素了
    // 并不是找到元素都要删除，如果节点有两个子节点，采用以右子树最小节点替换当前节点，并删除右子树节点的方式，
    // 拥有一个或者零个子节点，改变需要删除节点的父节点指针，然后删除
    else
    {

        printf("find it. %d\n", rootNode->item);
        // 有两个子节点
        if (rootNode->left != NULL && rootNode->right != NULL)
        {
            printf("%d has two children, delete the right child tree.\n", element);
            printf("find the min.\n");
            // 找到右子树的最小节点
            PtrNode min = FindMin(rootNode->right);
            printf("find the min is %d, the child tree root is %d.\n", min->item, rootNode->right->item);
            // ***用右子树最小的节点替换这个节点***
            rootNode->item = min->item;
            // 删除右子树最小的节点，此时 rootNode->right 为右子树的根
            rootNode->right = DeleteNode(rootNode->item, rootNode->right);
        }

        // 只有一个子节点，或者没有子节点
        else
        {
            PtrNode node = rootNode;
            if (rootNode->left == NULL && rootNode->right != NULL)
            {
                // 左节点为空，补右节点
                printf("%d has one right child %d.\n", element, rootNode->right->item);
                rootNode = rootNode->right;
            }
            else if (rootNode->right == NULL && rootNode->left != NULL)
            {
                // 右节点为空，补左节点
                printf("%d has one left child %d.\n", element, rootNode->left->item);
                rootNode = rootNode->left;
            }
            else
            {
                // 如果没有子节点，直接删除
                printf("no child. free and return NULL.\n");
                rootNode = NULL;
            }

            free(node);
        }
    }
    // 返回需要补上的节点
    return rootNode;
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