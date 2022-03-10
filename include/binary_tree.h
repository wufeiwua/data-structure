#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "tree.h"
typedef struct node
{
    int item;
    PtrNode left;
    PtrNode right;
} TreeNode;

typedef struct tree
{
    PtrNode root;
} BinaryTree;

PtrTree MakeTree();
void MakeEmpty();
PtrNode GetRoot(PtrTree tree);
PtrNode Find(int element, PtrNode rootNode);

PtrNode Insert(int element, PtrTree tree);
PtrNode Delete(int element, PtrTree tree);

#endif