#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node
{
    Element item;
    Position next;
} Node;

typedef struct list
{
    int length;
    Position head;
    Position last;
} LinkedList;

List MakeList()
{
    List list = (List)malloc(sizeof(LinkedList));
    Position head = (Position)malloc(sizeof(Node));
    head->next = NULL;
    head->item = NULL;
    list->head = head;
    list->last = head;
    list->length = 0;
    return list;
}

void MakeEmpty(List list)
{
    Position head = list->head;
    while (head != NULL)
    {
        Position temp = head->next;
        free(head);
        head = temp;
    }
}

int IsEmpty(const List list)
{
    return list->head->next == NULL;
}

int IsLast(const Position positon, const List list)
{
    return positon->next == NULL;
}

int Add(Element element, List list)
{
    Position newNode = (Position)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("cannot add, out of space.\n");
        return 0;
    }

    newNode->item = element;
    newNode->next = NULL;

    if (IsEmpty(list))
    {
        printf("set first node.\n");
        list->head->next = newNode;
    }
    list->last->next = newNode;
    list->last = newNode;
    list->length += 1;
    return 1;
}

int Remove(Element element, List list)
{
    Position pre = Previous(element, list);
    Position next = pre->next;
    // 前置节点是最后一个元素，说明不存在这个元素，则不进行任何操作
    if (!IsLast(pre, list))
    {
        pre->next = next->next;
        // 如果下一个节点是最后一个节点，则改变 last 指向位置
        if (next == list->last)
        {
            list->last = pre;
        }
        free(next);
        list->length -= 1;
    }
    return 1;
}

Position Previous(Element element, const List list)
{
    Position node = list->head;
    while (node->next != NULL && node->next->item != element)
    {
        node = node->next;
    }
    return node;
}

Position Find(Element element, const List list)
{
    Position cur = list->head->next;
    while (cur != NULL && cur->item != element)
    {
        cur = cur->next;
    }
    return cur;
}

void Reverse(List list)
{
    Position first = list->head->next;
    Position last = list->last;
    Position pre = NULL;
    Position cur = first;
    while (cur != NULL)
    {
        Position next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }

    list->head->next = last;
    list->last = first;
}

int GetSize(const List list)
{
    return list->length;
}

Element Retrieve(Position positon)
{
    if (positon != NULL)
    {
        return positon->item;
    }
    return NULL;
}

void PrintList(const List list, void (*pfunc)(Element element))
{
    Position cur = list->head->next;
    while (cur != NULL)
    {
        (*pfunc)(cur->item);
        cur = cur->next;
    }
}
