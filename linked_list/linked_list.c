#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
typedef struct node
{
    Element element;
    Position next;
} Node;

// 创建一个新表
List MakeList()
{
    // 申请一块新内存
    List L = (List)malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

// 判断是否为空
int IsEmpty(const List L)
{
    return L->next == NULL;
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
    Position P = L;
    // 当前元素的下一个节点的元素不相等继续找，如果相等了就返回
    while (P != NULL && P->next->element != E)
    {
        P = P->next;
    }
    return P;
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
    // 找当前元素的前一个元素，目的在于可直接修改该元素的指针即可
    Position P = FindPrevious(E, L);
    // 当前元素
    Position cur;
    // 如果 E 不在列表中，P 应该是最后一个节点，因为 E不在链表中所以什么也不需要做
    // 如果 E 是链表中的最后一个元素，P 是倒数第二个节点，cur->next 是 NULL，释放最后一个节点的内存，然后将 P 指向 NULL 也就是(cur->next)
    if (!IsLast(P, L))
    {
        cur = P->next;
        // 修改指针，指向当前元素的下一个元素
        P->next = cur->next;
        // 释放内存
        free(cur);
        return 0;
    }
    return 0;
}

// 在某个位置后插入一个元素
int InsertPositon(Element E, List L, Position P)
{
    if (P == NULL)
    {
        printf("cannot insert, position is not exist\n");
        return -1;
    }
    Position newP = (Position)malloc(sizeof(Node));
    if (newP == NULL)
    {
        return -1;
    }
    newP->element = E;
    // 新节点的下一个节点等于原位置的下一个节点
    newP->next = P->next;
    // 将原位置的下一个节点置位新的节点
    P->next = newP;
    return 0;
}

// 插入一个元素到链表尾端
int Insert(Element E, List L)
{
    Position P = FindLast(L);
    return InsertPositon(E, L, P);
}

void PrintList(const List L, void (*pfunc)(Element E))
{
    Position cur = L->next;
    while (cur != NULL)
    {
        (*pfunc)(cur->element);
        cur = cur->next;
    }
}
