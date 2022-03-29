#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int set_fd(uint64_t *fd);
void hello(int num, void (*pfunc)(int));
void say(int num);
void setStr(char *);
void set(char **);

int main(int argc, char *argv[])
{
    // uint64_t fd;
    // set_fd(&fd);
    // int *num = (int *)fd;
    // printf("%d\n", *num);
    printf("%p\n", &say);
    printf("%p\n", say);
    hello(10, say);
    hello(11, &say);

    char **str = (char **)malloc(sizeof(char *));
    set(str);
    printf("====>the str is.%s\n", *str);

    char *strs = NULL;
    setStr(strs);
    printf("====>the strs is.%s\n", strs);
    printf("the addr of main strs%p\n", &strs);
    return 0;
}

// int set_fd(uint64_t *fd)
// {
//     int num = 100;
//     *fd = &num;
//     return 0;
// }

void hello(int num, void (*pfunc)(int))
{
    (*pfunc)(num);
    pfunc(num);
}

void say(int num)
{
    printf("hello%d\n", num);
}

void setStr(char *str)
{
    printf("the addr of func strs%p\n", &str);
    str = "hello!";
    printf("the addr of func2 strs%c\n", *str);
}

void set(char **str)
{
    *str = "hello";
}