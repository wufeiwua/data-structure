#ifndef _LIST_H
#define _LIST_H

struct node;
struct list;
typedef struct node *Position;
typedef struct list *List;
typedef void *Element;

List MakeList();
void MakeEmpty(List list);
int IsEmpty(const List list);
int IsLast(const Position positon, const List list);

int Add(Element element, List list);
int Remove(Element element, List list);
Position Previous(Element element, const List list);
Position Find(Element element, const List list);
void Reverse(List list);

void PrintList(const List list, void (*pfunc)(Element element));
Element Retrieve(Position positon);

#endif