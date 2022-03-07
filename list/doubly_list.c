#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "list.h"

typedef struct node
{
    Element item;
    Position next;
    Position prev;
} Node;

typedef struct list
{
    int length;
    Position first;
    Position last;
} DoublyLinkedList;

List MakeList()
{
    List list = (List)malloc(sizeof(DoublyLinkedList));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}
void MakeEmpty(List list);

int IsEmpty(const List list)
{
    return list->first == NULL;
}

int IsLast(const Position positon, const List list)
{
    return positon == list->last;
}

int Add(Element element, List list)
{
    Position newNode = (Position)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("cannt add node, out of space.\n");
        return 0;
    }

    newNode->item = element;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (IsEmpty(list))
    {
        list->first = newNode;
        list->last = newNode;
        return 1;
    }

    Position last = list->last;
    newNode->prev = last;
    last->next = newNode;
    // 移动 last 指针
    list->last = newNode;
    list->length += 1;
    return 1;
}

int Remove(Element element, List list)
{
    Position curr = Find(element, list);
    if (curr == NULL)
    {
        printf("cannot remove, node is not exist.\n");
        return 0;
    }
    Position prev = curr->prev;
    Position next = curr->next;

    // 断掉中间节点，连接两端节点
    if (prev == NULL)
    {
        // 删除头节点
        list->first = next;
        next->prev = NULL;
    }
    else if (next == NULL)
    {
        // 删除尾节点
        list->last = prev;
        prev->next = NULL;
    }
    else
    {
        prev->next = curr->next;
        next->prev = curr->prev;
    }
    // 释放内存
    free(curr);
    list->length -= 1;
    return 1;
}

Position Previous(Element element, const List list)
{
    Position curr = Find(element, list);
    if (curr != NULL)
    {
        return curr->prev;
    }
    return NULL;
}

Position Find(Element element, const List list)
{
    Position curr = list->first;
    while (curr != NULL && curr->item != element)
    {
        curr = curr->next;
    }
    return curr;
}

void Reverse(List list)
{
    printf("reverse list.\n");
    Position first = list->first;
    Position last = list->last;
    Position curr = list->first;
    Position prev = NULL;
    while (curr != NULL)
    {
        Position next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    list->first = last;
    list->last = first;
}

int GetSize(const List list)
{
    return list->length;
}

void PrintList(const List list, void (*pfunc)(Element element))
{
    printf("asc print.\n");
    Position cur = list->first;
    while (cur != NULL)
    {
        (*pfunc)(cur->item);
        cur = cur->next;
    }
    printf("desc print.\n");
    cur = list->last;
    while (cur != NULL)
    {
        (*pfunc)(cur->item);
        cur = cur->prev;
    }
}

Element Retrieve(Position positon)
{
    return positon->item;
}