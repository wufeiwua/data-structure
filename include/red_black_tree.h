#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

// #define RED 0
// #define BLACK 1
// #define Color int
typedef enum Color
{
    RED,
    BLACK,
} Color;
typedef int ElementType;
typedef struct node
{
    struct node *left;
    struct node *right;
    struct node *parent;
    Color color;
    ElementType value;
} Node;

typedef Node *PtrNode;
typedef PtrNode *PtrRoot;

void Insert(ElementType value, PtrRoot root);
void Delete(ElementType value, PtrRoot root);
PtrNode Get(ElementType value, PtrRoot root);

#endif