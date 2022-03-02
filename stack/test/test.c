#include <stdio.h>
#include <stack.h>

void print_stack(Element);

int main(int argc, char const *argv[])
{
    Stack stack = MakeStack();
    Push("1", stack);
    Push("2", stack);
    Push("3", stack);
    Push("4", stack);
    Push("5", stack);

    Pop(stack);
    Pop(stack);
    Pop(stack);
    Pop(stack);
    Pop(stack);
    Pop(stack);
    Pop(stack);

    Push("6", stack);
    Push("7", stack);
    Push("8", stack);
    Push("9", stack);
    Push("10", stack);
    Push("11", stack);
    Push("12", stack);

    PrintStack(stack, &print_stack);
    PrintStack(stack, &print_stack);
    MakeEmpty(stack);
    PrintStack(stack, print_stack);

    printf("\n");
    return 0;
}

void print_stack(Element e)
{
    // 强转
    char *s = (char *)e;
    printf("%s\n", s);
}
