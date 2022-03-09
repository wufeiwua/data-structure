#include <stdio.h>
#include "binary_tree.h"

void print_tree_inorder(PtrNode rootNode);
void print_tree_preorder(PtrNode rootNode);
void print_tree_postorder(PtrNode rootNode);

int main(int argc, char const *argv[])
{
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    int n5 = 5;
    int n6 = 6;
    int n7 = 7;
    int n8 = 8;
    int n9 = 9;
    PtrTree tree = MakeTree();
    PtrNode root = Insert(&n6, NULL);
    tree->root = root;
    Insert(&n2, root);
    Insert(&n1, root);
    Insert(&n3, root);
    Insert(&n4, root);
    Insert(&n8, root);
    Insert(&n5, root);
    Insert(&n7, root);
    Insert(&n9, root);

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
    int item = *(int *)rootNode->item;
    print_tree_inorder(rootNode->left);
    printf("%d\n", item);
    print_tree_inorder(rootNode->right);
}

void print_tree_preorder(PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        return;
    }
    int item = *(int *)rootNode->item;
    printf("%d\n", item);
    print_tree_inorder(rootNode->left);
    print_tree_inorder(rootNode->right);
}

void print_tree_postorder(PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        return;
    }
    int item = *(int *)rootNode->item;
    print_tree_inorder(rootNode->left);
    print_tree_inorder(rootNode->right);
    printf("%d\n", item);
}
