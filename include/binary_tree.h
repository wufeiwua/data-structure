#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "tree.h"
typedef struct node
{
    Element item;
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
PtrNode Find(Element element, PtrNode rootNode);

PtrNode Insert(Element element, PtrNode rootNode);
int Delete(Element element, PtrNode rootNode);

#endif