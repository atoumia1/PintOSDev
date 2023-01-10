#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "lib/user/syscall.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void syscall_init (void);
void exit(int status);

#endif /* userprog/syscall.h */
