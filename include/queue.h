#ifndef _QUEUE_H
#define _QUEUE_H

struct node;
typedef struct node *PtrNode;
typedef PtrNode Queue;
typedef void *Element;

// 初始化队列
Queue MakeQueue(void);

// 置空队列
void MakeEmpty(Queue q);

// 是否为空
int IsEmpty(Queue q);

// 入队
void Enqueue(Element e, Queue q);

// 出队
Element Dequeue(Queue q);

void PrintQueue(Queue q, void (*pfunc)(Element e));
#endif