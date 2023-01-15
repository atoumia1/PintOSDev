/* klaar@ida

   pintos -v --fs-disk=2 -p ../examples/crack -a crack -p ../examples/shellcode -a shellcode -- -f -q run 'shellcode'

   -*- Woahhh, have fun -*-
   http://www.phrack.org/issues.html?issue=49&id=14#article
   http://www.phrack.org/issues.html?issue=57&id=15#article

   Somewhat simpler to achieve in Pintos actually.
 */

#include <syscall.h>
#include <stdio.h>
/* This it the below assembly code in binary form. It runs. To get it,
  just compile the code below and use the debugger to dump the code
  in the main function. */

char shellcode[] =
  "\x90\x90\x90\x90\x90\xe9\x0b\x00"
  "\x00\x00\x6a\x05\xcd\x30\x31\xc0"
  "\x50\x40\x50\xcd\x30\xe8\xf0\xff"
  "\xff\xff""test";

/* And this is rather scary amazing...  This is also the below
 * assembly code in binary form, but now using ONLY alphanumeric
 * characters. It works flawless...  Using something like isalpha() on
 * input does not prevent crackers to exploit buffer overflows.
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
