#include <stdio.h>
#include "queue.h"

void print_queue(Element e);

int main(int argc, char const *argv[])
{
    Queue q = MakeQueue();
    Enqueue("1", q);
    Enqueue("2", q);
    Enqueue("3", q);
    Enqueue("4", q);
    Enqueue("5", q);
    Enqueue("6", q);
    Enqueue("7", q);
    Dequeue(q);
    PrintQueue(q, print_queue);
    return 0;
}

void print_queue(Element e)
{
    char *s = (char *)e;
    printf("%s\n", s);
}
