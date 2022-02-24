#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

struct node;                    // 定义节点
typedef void *Element;          // 定义指向任意元素的指针，表示链表中的具体数据
typedef struct node *PtrToNode; // 定义指向节点的指针
typedef PtrToNode List;         // List 就是表头（哑结点）用于指向这个表
typedef PtrToNode Position;     // Position 具体指向表中的某一个节点

// 创建一个新表
List MakeList();

// 判断是否为空
int IsEmpty(const List L);

// 判断是否为链表的最后一个元素
int IsLast(Position P, const List L);

// 查找某个元素的位置
Position Find(const Element E, const List L);

// 查找某个元素的上一个位置
Position FindPrevious(Element E, List L);

// 获取最后一个节点位置
Position FindLast(List L);

// 删除某个元素
int Delete(Element E, List L);

// 插入一个元素到指定位置
int InsertPositon(Element E, List L, Position P);

// 插入一个元素到链表尾端
int Insert(Element E, List L);

Position Header(const List L);
Position First(const List L);
Position Advance(Position P);
Element Retrieve(Position P);

void PrintList(const List L, void (*pfunc)(Element E));

#endif