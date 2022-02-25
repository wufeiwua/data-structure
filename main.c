#include <stdio.h>
#include <stdint.h>

int set_fd(uint64_t *fd);
void hello(int num, void (*pfunc)(int));
void say(int num);

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