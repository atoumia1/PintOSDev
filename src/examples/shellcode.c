/* klaar@ida

code based on Litborn, J. (2022)

Litborn, J.(2022), Pintos, Available from: https://gitlab.liu.se/johli603/pintos/-/blob/master_origin/src/examples/crack.c
*/

#include <syscall.h>
#include <stdio.h>

/* This it the below assembly code in binary form. It runs. To get it,
  just compile the code below and use the debugger to dump the code
  in the main function. */

char shellcode[] =
  "\x90\x90\x90\x90\x90\xe9\x0b\x00"
  "\x00\x00\x6a\x02\xcd\x30\x31\xc0"
  "\x50\x40\x50\xcd\x30\xe8\xf0\xff"
  "\xff\xff""crack";

/*
  The shellcode above can be translated to the following steps
  
  0:  90                      nop             -- no operation value, acts as a place holder
  1:  90                      nop
  2:  90                      nop
  3:  90                      nop
  4:  90                      nop
  5:  e9 0b 00 00 00          jmp    0x15     -- jumps to position 15
  a:  6a 02                   push   0x2      -- exec syscall number
  c:  cd 30                   int    0x30
  e:  31 c0                   xor    eax,eax  -- returns value of 0
  10: 50                      push   eax      -- pushes new 0 value
  11: 40                      inc    eax      -- incriments value of eax by 1
  12: 50                      push   eax      -- pushes new 1 value
  13: cd 30                   int    0x30     -- creates interupt
  15: e8 f0 ff ff ff          call   0xa      -- calls a function, '0xa' is the hex value of an ascii newline character
  It then takes the input "echo x y z" and uses it with the syscall exec
  
*/

int main( void )
{
  int *ret; /* A local variable is stored on the stack. */

  ret = (int *)&ret + 2;   /* Two steps above in the stack is the
                            * address to continue at when main
                            * return... the normal function return
                            * address. */
  (*ret) = (int)shellcode; /* We overwrite it with the address to the
                            * shell code. This will check that the
                            * shell code works as expected. */
  return 0;
}
