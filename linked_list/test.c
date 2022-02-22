#include <stdio.h>
#include "linked_list.h"

int main(int argc, char *argv[])
{
    List L = MakeList();
    Insert("1", L);
    Insert("2", L);
    Insert("3", L);
    Insert("4", L);
    Insert("5", L);
    Position P = Find("1", L);
    InsertPositon("6", L, P);
    PrintList(L);
    return 0;
}

