#include <stdio.h>
#include "binary_tree.h"

void print_tree_inorder(PtrNode rootNode);
void print_tree_preorder(PtrNode rootNode);
void print_tree_postorder(PtrNode rootNode);

int main(int argc, char const *argv[])
{

    PtrTree tree = MakeTree();

    Insert(1, tree);
    Insert(2, tree);
    Insert(3, tree);
    Insert(4, tree);
    Insert(5, tree);
    Insert(6, tree);
    Insert(7, tree);

    PtrNode root = GetRoot(tree);
    printf("inorder===\n");
    print_tree_inorder(root);
    printf("preorder===\n");
    print_tree_preorder(root);
    printf("postorder===\n");
    print_tree_postorder(root);

    // find
    Find(1, tree);
    root = GetRoot(tree);
    printf("inorder===\n");
    print_tree_inorder(root);
    printf("preorder===\n");
    print_tree_preorder(root);
    printf("postorder===\n");
    print_tree_postorder(root);

    // delete
    Delete(4, tree);
    root = GetRoot(tree);
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
    int item = rootNode->item;
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
    int item = rootNode->item;
    printf("%d\n", item);
    print_tree_preorder(rootNode->left);
    print_tree_preorder(rootNode->right);
}

void print_tree_postorder(PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        return;
    }
    int item = rootNode->item;
    print_tree_postorder(rootNode->left);
    print_tree_postorder(rootNode->right);
    printf("%d\n", item);
}
