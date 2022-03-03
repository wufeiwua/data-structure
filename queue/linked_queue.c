#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct node
{
    struct node *next;
    Element element;
} Node;

// 初始化队列
Queue MakeQueue(void)
{
    Queue q = (Queue)malloc(sizeof(Node));
    return NULL;
}

// 置空队列
void MakeEmpty(Queue q)
{
    Node *front = q;
    while (front->next != NULL)
    {
        Node *next = front->next;
        free(front);
        front = next;
    }
}

// 是否为空
int IsEmpty(Queue q)
{
    return q->next == NULL;
}

// 入队
void Enqueue(Element e, Queue q)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("cannot enqueue, out of space\n");
        return;
    }
    Node *tail = q;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    newNode->element = e;
    tail->next = newNode;
}

// 出队
Element Dequeue(Queue q)
{
    Node *front = q->next;
    if (front == NULL)
    {
        printf("cannot dequeue, queue is empty");
        return NULL;
    }
    q->next = front->next;
    Element e = front->element;
    free(front);
    return e;
}

void PrintQueue(Queue q, void (*pfunc)(Element e))
{
    Node *front = q;
    while (front->next != NULL)
    {
        front = q->next;
        Element e = front->element;
        pfunc(e);
    }
}