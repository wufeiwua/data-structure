#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
typedef struct node
{
    Element element; // 当前元素
    Position pre;    // 上一个节点
    Position next;   // 下一个节点
} Node;

// 创建一个新表
List MakeList()
{
    List L = (List)malloc(sizeof(Node));
    L->pre = NULL;
    L->next = NULL;
    return L;
}

// 判断是否为空
int IsEmpty(const List L)
{
    return L->next == NULL && L->pre == NULL;
}

// 判断是否为链表的最后一个元素
int IsLast(Position P, const List L)
{
    return P->next == NULL;
}

// 查找某个元素的位置
Position Find(const Element E, const List L)
{
    Position P = L->next;
    // 如果元素不相等继续向下找，如果相等了就返回
    while (P != NULL && P->element != E)
    {
        P = P->next;
    }
    return P;
}

// 查找某个元素的上一个位置
Position FindPrevious(Element E, List L)
{
    Position P = Find(E, L);
    if (P == NULL)
    {
        return NULL;
    }
    return P->pre;
}

// 获取最后一个节点位置
Position FindLast(List L)
{
    Position P = L;
    while (P->next != NULL)
    {
        P = P->next;
    }
    return P;
}

// 删除某个元素
int Delete(Element E, List L)
{
    Position curNode = Find(E, L);
    if (curNode == NULL)
    {
        // not in
        return -1;
    }
    Position preNode = curNode->pre;
    Position nextNode = curNode->next;
    if (!IsLast(curNode, L))
    {
        preNode->next = curNode->next;
        nextNode->pre = curNode->pre;
    }
    else
    {
        preNode->next == NULL;
    }
    free(curNode);
    return 0;
}

// 插入一个元素到指定位置
int InsertPositon(Element E, List L, Position P)
{

    if (P == NULL)
    {
        printf("cannot insert, position is not exist\n");
        return -1;
    }
    Position newNode = (Position)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        // 没有足够的内存
        return -1;
    }
    Position nextNode = P->next;
    newNode->element = E;
    newNode->next = nextNode;

    // 插入中间位置
    P->next = newNode;
    // 前节点可能是空的， NPE!!!
    if (nextNode != NULL)
    {
        nextNode->pre = newNode;
    }
    return 0;
}

// 插入一个元素到链表尾端
int Insert(Element E, List L)
{
    Position P = FindLast(L);
    InsertPositon(E, L, P);
    return 0;
}

Position Header(const List L);
Position First(const List L);
Position Advance(Position P);
Element Retrieve(Position P);

void PrintList(const List L, void (*pfunc)(Element E))
{
    Position cur = L->next;
    while (cur != NULL)
    {
        (*pfunc)(cur->element);
        cur = cur->next;
    }
}