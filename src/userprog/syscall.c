/* COMMENTS USING THIS FORMAT ARE PERMINANT*/
// COMMENTS USING THIS FORMAT ARE TEMPORARY-

#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

/* additional includes from base */
#include "lib/user/syscall.h"
#include "threads/vaddr.h"
#include "lib/stdio.h"
#include "devices/shutdown.h"
#include "lib/string.h"
#include "threads/palloc.h"
#include "devices/input.h"
#include "filesys/filesys.h"
#include "filesys/file.h"

/*delcares syscall_handler and gives is access to the 
structure intr_frame to allow it to use interupt frames */
static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  /* creates an interput as 0x30 points to the interupt vector table */
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

/* syscalls: */

/*halt acts as an unclean exit and doesn't provide any additional
info about the exit to the user */
void halt(void)
{
  /* Debugging */
  printf("Halt Syscall!\n");
  /* Calls in order to shut down machine */
  shutdown_power_off();
}

/* Exit is used to properly terminate a user program, returning an exit
message or */
void exit(int status)
{
  if (status == EXIT_FAILURE || status > 0)
  {
    printf("%s: exit failure(%d)\n", thread_name(), status);
  }
  struct thread *cur = thread_current();
  cur->exit_code = status;
  printf("%s: exit(%d)\n", cur->name, cur->exit_code);
  thread_exit();
}

/* Create, as the name suggests, creates a file using the premade
function 'filesys_create'. Creating a file does not open it. */
bool create(const char *file, unsigned initial_size)
{
  printf("test create\n");
  /* Filesys_create is defined in filesys/filesys.c, accepting
  two paramaters being a file name and file size. Filesys_create
  uses inodes (index nodes) as well as the information taken from
  the user to create a file in user disk space*/
  return filesys_create(file, initial_size);
}

bool remove(const char *file)
{
  printf("test remove\n");

  return filesys_remove(file);
}

/* Syscall handler has access to the structure 'int_frame' in order
to create interupts when a system call is requested, defining it as
'f' so we access variables within the struct such as 'esp' or 'eax' */
static void
syscall_handler (struct intr_frame *f UNUSED)
{
  //int sys_code = 4;
  
  //refuses to work atm, doesnt get syscodes when called to
  // does that mean they're not on the stack, or we call to them wrong
  //or stack doesnt load them properly(least likely)
  int sys_code = *(int*)f->esp;
  
  /* Switch statement uses 'sys_code' in order to determine the next syscall
  a user program is requesting access to. Each case's name has already
  been defined within syscall-nr.h as enum values */
  switch(sys_code)
  {
    case SYS_HALT:
    {
      halt();
      break;
    }
    case SYS_EXIT:
    {
      int status = (unsigned)(f->esp + 4);
      exit(status);
      break;
    }
    case SYS_CREATE:
    {
      printf("filename = %s\n", (const char *)(f->esp + 4));
      const char *cre_name = (const char *)(f->esp + 4);
      unsigned int cre_size =  (unsigned)(f->esp + 8);
      bool testCreate = create(cre_name, cre_size);
      f->eax = testCreate;
      printf("test create\n");
      break;
    }
    case SYS_REMOVE:
    {
      printf("filename = %s\n", (const char *)(f->esp + 4));
      const char *rem_name = (const char *)(f->esp + 4);
      bool testRemove = remove(rem_name);
      f->eax = testRemove;
      printf("test remove\n");
      break;
    }
    // default:
    // {
    //   printf("NO SYSCALL!");
    // }
  }
  printf ("system call!\n");
  thread_exit ();
}