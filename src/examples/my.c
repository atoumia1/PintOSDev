#include <stdio.h>
#include <syscall.h>
#include "userprog/syscall.h"
#include "lib/stdio.h"
#include <syscall-nr.h>
#include "threads/interrupt.h"

int main(void)
{
    printf("Test 1\n");
    create("text.txt", 0);
    printf("Test 2\n");
    remove("test.txt");
    printf("Test 3\n");
    halt();
    //exit(0);
    //remove("text.txt");
    //exec("hello again!!");
    return 0;
}
