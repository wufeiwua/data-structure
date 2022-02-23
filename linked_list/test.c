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
    Position NP = Find("10", L);
    if (NP == NULL)
    {
        printf("NP & inser NP\n");
        InsertPositon("11", L, NP);
    }
    InsertPositon("6", L, P);

    PrintList(L);
    return 0;
}
