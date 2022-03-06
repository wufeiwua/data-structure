#include <stdio.h>
#include "list.h"

void print_list(Element element);

int main(int argc, char const *argv[])
{
    List list = MakeList();
    Add("1", list);
    Add("2", list);
    Add("3", list);
    Add("4", list);
    Add("5", list);
    Add("6", list);
    Add("7", list);
    PrintList(list, print_list);

    Reverse(list);
    PrintList(list, print_list);

    Remove("1", list);
    Remove("2", list);
    Remove("3", list);
    PrintList(list, print_list);

    Add("1", list);
    Add("2", list);
    Add("3", list);
    PrintList(list, print_list);
    return 0;
}

void print_list(Element element)
{
    char *s = (char *)element;
    printf("%s\n", s);
}
