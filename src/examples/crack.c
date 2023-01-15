/* Crack program prints assci art in show that exploit has worked 

code based on Litborn, J. (2022)

Litborn, J.(2022), Pintos, Available from: https://gitlab.liu.se/johli603/pintos/-/blob/master_origin/src/examples/crack.c
*/

#include <syscall.h>
#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
int
main (void)
{
  // const char* msg[5] = {
  //   " Y   Y  OOO  O   O | RRR  EEEE    DDD    OOO  N   N EEEE \n",
  //   " Y   Y O   O O   O | R  R E       D  D  O   O NN  N E    \n",
  //   "  YYY  O   O O   O   RRR  EEE     D   D O   O N N N EEE  \n",
  //   "   Y   O   O O   O   R  R E       D  D  O   O N  NN E    \n",
  //   "   Y    OOO   OOO    R  R EEEE    DDD    OOO  N   N EEEE \n"
  // };
  // int i;

  // for (i = 0; i < 5; ++i)
  // {
  //   write (STDOUT_FILENO, msg[i], strlen(msg[i]));
  // }
  remove("test.txt");
=======
const char* exploit = "echo x y z";
>>>>>>> henry

int main (void)
{
  exec(exploit);
  return 0;
}
