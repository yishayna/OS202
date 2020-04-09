#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int
main(int argc, char *argv[])
{
  int x = memsize();
  printf(1,"The process is using: %x\n",x);
  printf(1,"Allocating more memory\n");
  void *m1 = malloc(1024*2);
  int y = memsize();
  printf(1,"The process is using: %x\n",y);
  printf(1,"Freeing memory\n");
  free(m1);
  int z = memsize();
  printf(1,"The process is using: %x\n",z);
  exit(0);
}
