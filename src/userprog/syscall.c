#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "lib/user/syscall.h"
#include "threads/vaddr.h"
#include "lib/stdio.h"
#include "devices/shutdown.h"
#include "lib/string.h"
#include "threads/palloc.h"
#include "devices/input.h"
#include "filesys/filesys.h"
#include "filesys/file.h"


// static int memread_user(void *src, void *des, size_t bytes);

static void syscall_handler (struct intr_frame *);

const char* name;
unsigned int* initial_size;

// tid_t tid;

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  //creates an interput as 0x30 points to the interupt vector table
}

//syscalls:

void halt(void)
{
  printf("Halt Syscall!\n");
  shutdown_power_off();
}

// void exit(int status)
// {
//    char test_name = thread_current->name[];
//    printf("Exiting: %s . (%d)\n", test_name, status);
// }
  

bool create(const char *file, unsigned initial_size)
{
  printf("test create\n");
  return filesys_create(file, initial_size);
}

bool remove(const char *file)
{
  printf("test remove\n");
  return filesys_remove(file);
}

pid_t exec(const char *cmdline)
{
  
  pid_t pid = process_execute(cmdline);
    if (pid == TID_ERROR)
      return -1;
  printf("test: %s\n", cmdline);
  return pid;
}


//FIX OPEN!!!!!!!!!!!!
/*
int open(const char *file)
{
  struct file *f = filesys_open(file);
  if (f == NULL){
     return -1;
  }
  // Open file
  // struct file *f = filesys_open(file);
  // if (f == NULL)
  //   return -1;
  // // Find first available fd, 0/1 are reserved for stdin/stdout
  // int fd = 2;
  // // char fd_table[128];
  // while (fd < 16)
  // {
  //   if (thread_current()->name[fd] == NULL)
  //   {
  //     thread_current()->name[fd] = f;
  //     printf("opened file %s at fd %d\n", file, fd);
  //     return fd;
  //   }
  //   fd++;
  // }
  // return -1;
}*/

static void
syscall_handler(struct intr_frame *f UNUSED)
{
  //test
  //int *esp = f->esp;
  //int sys_code = *(int*)f->esp;
  
  int *esp = f->esp;
  int sys_code = *esp;

  //int sys_code = 4;
  
  switch(sys_code)
  {
    case SYS_HALT:
    {
      halt();
      break;
    }
    
    //argv_addr?
    //how much do we dec stack pointer for it to fit in mem add?
    //          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    case SYS_CREATE:
    {
      /* char* parameter1 = *(char*) f->esp + 4;
      unsigned int parameter2 = *(unsigned int*) f ->esp + 8;
      parameter1 = name;
      parameter2 = initial_size;
      filesys_create(name, initial_size);
      printf("sys_create !!!!! \n"); */
      printf("filename = %s\n", (const char *)*(esp + 1));
      
      bool testCreate = create((const char *)*(esp + 1), (unsigned)*(esp + 2));
      f->eax = testCreate;
      printf("test create\n");
      break;
    }
    case SYS_REMOVE:
    {
      printf("filename = %s\n", (const char *)*(esp + 1));
      bool testRemove = remove((const char *)*(esp + 1));
      f->eax = testRemove;
      break;
    }
    case SYS_EXIT:
    {
      struct thread *cur = thread_current();
      char* fname = cur->name;
      // exit(status)
      printf("exit status = %d, filename = %s\n", *((int*)*(esp + 1)), fname);   //(const char *)*(esp + 1)); *((int *)f->esp+1)
      break;
    }
    case SYS_EXEC:
    {
      int testExec = exec((const char *)*(esp + 1));
      f->eax = testExec;
      break;
    }
    // case SYS_OPEN:
    // {
    //   int testOpen = open((const char *)*(f->esp + 1));
    //   f->eax = testOpen;
    //   break;
    // }
    default:
    {
      break;
    }
    
  }
  
}



// bool syscreate(){
//   return filesys_create(file, initial_size);
// }
