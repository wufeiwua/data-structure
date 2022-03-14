#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "tree.h"
typedef struct node
{
    int item;
    PtrNode left;
    PtrNode right;
    int height;     // AVL_Tree
    PtrNode parent; // Splay_Tree
} TreeNode;

typedef struct tree
{
    PtrNode root;
} BinaryTree;

PtrTree MakeTree();
PtrNode MakeEmpty(PtrNode rootNode);
PtrNode GetRoot(PtrTree tree);
PtrNode Find(int element, PtrTree tree);

PtrNode Insert(int element, PtrTree tree);
PtrNode Delete(int element, PtrTree tree);

#endif