#ifndef _STACK_H
#define _STACK_H

struct node;
typedef struct node *PtrNode;
typedef PtrNode Stack;
typedef void *Element;
typedef void (*PtrFunc)(Element);

int IsEmpty(Stack s);

// 初始化一个栈
Stack MakeStack(void);

// 置空栈
void MakeEmpty(Stack s);

// 插入一个元素
void Push(Element e, Stack s);

// 移出一个元素
void Pop(Stack s);

// 获取栈顶元素
Element Top(Stack s);

void DisposeStack(Stack s);

void PrintStack(Stack s, PtrFunc);

#endif