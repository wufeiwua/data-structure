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

PtrNode Insert(ElementType value, PtrNode node);
PtrNode Delete(ElementType value);
PtrNode Get(ElementType value);

#endif