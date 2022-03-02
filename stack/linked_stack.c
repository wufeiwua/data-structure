/*
 栈 单链表实现


 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc free
#include "stack.h"

typedef struct node
{
    struct node *next;
    Element element;
} Node;

int IsEmpty(Stack s)
{
    return s->next == NULL;
}

// 初始化一个栈
Stack MakeStack(void)
{
    Stack s = (Stack)malloc(sizeof(Node));
    if (s == NULL)
    {
        printf("cannot create stack, out of space\n");
    }
    s->next = NULL;
    return s;
}

// 置空栈
void MakeEmpty(Stack s);

// 插入一个元素
void Push(Element e, Stack s)
{
    Node *top = s->next;
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("cannot push element, out of space\n");
        return;
    }
    newNode->element = e;
    s->next = newNode;
    newNode->next = top;
}

// 移出一个元素
void Pop(Stack s)
{
    Node *top = s->next;
    if (top == NULL)
    {
        printf("cannot pop element, stack is empty\n");
        return;
    }
    s->next = top->next;
    free(top);
}

// 获取栈顶元素
Element Top(Stack s)
{
    Node *top = s->next;
    if (top != NULL)
    {
        return top->element;
    }
    return NULL;
}

void DisposeStack(Stack s);

void PrintStack(Stack s, PtrFunc pfunc)
{
    printf("print stack\n");
    while (!IsEmpty(s))
    {
        pfunc(s->next->element);
        Pop(s);
    }
}
