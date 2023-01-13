#include <stdio.h>
#include <syscall.h>

int
main (int argc, char *argv[]) 
{
  bool success = true;
  int i;
  
  for (i = 1; i < argc; i++)
    if (!create (argv[i], 0)) 
      {
        printf ("%s: remove failed\n", argv[i]);
        success = false; 
      }
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

