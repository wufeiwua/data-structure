#include <stdio.h>
#include "red_black_tree.h"

void print_tree_inorder(PtrNode rootNode);
void print_tree_preorder(PtrNode rootNode);
void print_tree_postorder(PtrNode rootNode);

int main(int argc, char const *argv[])
{
    PtrNode root = NULL;
    root = Insert(30, root);
    root = Insert(15, root);
    root = Insert(10, root);
    root = Insert(5, root);
    root = Insert(20, root);
    root = Insert(70, root);
    root = Insert(60, root);
    root = Insert(50, root);
    root = Insert(40, root);
    root = Insert(55, root);
    root = Insert(65, root);
    root = Insert(85, root);
    root = Insert(80, root);
    root = Insert(90, root);
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