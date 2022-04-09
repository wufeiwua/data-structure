#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree.h"

void print_tree_inorder(PtrNode rootNode);
void print_tree_preorder(PtrNode rootNode);
void print_tree_postorder(PtrNode rootNode);

int main(int argc, char const *argv[])
{
    PtrNode root = NULL;
    Insert(30, &root);
    Insert(15, &root);
    Insert(10, &root);
    Insert(5, &root);
    Insert(20, &root);
    Insert(70, &root);
    Insert(60, &root);
    Insert(50, &root);
    Insert(40, &root);
    Insert(45, &root);
    Insert(55, &root);
    Insert(65, &root);
    Insert(85, &root);
    Insert(80, &root);
    Insert(90, &root);
    Insert(46, &root);

    Delete(46, &root);
    Delete(55, &root);
    Delete(70, &root);
    Delete(40, &root);
    Delete(30, &root);

    printf("inorder===\n");
    print_tree_inorder(root);
    printf("preorder===\n");
    print_tree_preorder(root);
    printf("postorder===\n");
    print_tree_postorder(root);

    return 0;
}

void print_tree_inorder(PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        return;
    }
    print_tree_inorder(rootNode->left);
    printf("%d:color(%d)\n", rootNode->value, rootNode->color);
    print_tree_inorder(rootNode->right);
}

void print_tree_preorder(PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        return;
    }
    printf("%d:color(%d)\n", rootNode->value, rootNode->color);
    print_tree_preorder(rootNode->left);
    print_tree_preorder(rootNode->right);
}

void print_tree_postorder(PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        return;
    }
    print_tree_postorder(rootNode->left);
    print_tree_postorder(rootNode->right);
    printf("%d:color(%d)\n", rootNode->value, rootNode->color);
}