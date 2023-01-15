/* Crack program prints assci art in show that exploit has worked 

code based on Litborn, J. (2022)

Litborn, J.(2022), Pintos, Available from: https://gitlab.liu.se/johli603/pintos/-/blob/master_origin/src/examples/crack.c
*/

#include <syscall.h>

const char* rmthis = "test";

int main (void)
{
  remove(rmthis);
  return 0;
}
