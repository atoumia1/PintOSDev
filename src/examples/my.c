#include <stdio.h>
#include <syscall.h>

int main (void)
{
    //printf("Hello, World\n");
    create("text.txt", 100);
    remove("text.txt");
    exec("hello again!!");
    return 0;
}
