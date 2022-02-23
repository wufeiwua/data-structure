#include <stdio.h>
#include <stdint.h>

int set_fd(uint64_t *fd);

int main(int argc, char *argv[])
{
    uint64_t fd;
    set_fd(&fd);
    int *num = (int *)fd;
    printf("%d\n", *num);
    return 0;
}

int set_fd(uint64_t *fd)
{
    int num = 100;
    *fd = &num;
    return 0;
}