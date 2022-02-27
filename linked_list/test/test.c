#include <stdio.h>
#include "linked_list.h"
void print_list(Element E);

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

    PrintList(L, &print_list);
    return 0;
}

void print_list(Element E)
{
    char *s = (char *)E;
    printf("%s\n", s);
}
