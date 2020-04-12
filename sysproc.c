#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
  if(argint(0, &status) < 0)
    return -1;
  exit(status);
  return 0;  // not reached
}

int
sys_set_ps_priority(void)
{
  int priority;
  if(argint(0, &priority)<0)
    panic("cannot get ps priority");
  myproc()->ps_priority = priority; 
  return myproc()->ps_priority;
}

int 
sys_set_cfs_priority(void)
{
  int pr;
  if(argint(0, &pr)<0)
    panic("cannot get cfs priority");
  if (pr<1 || pr>3)
    return -1;
  myproc()->cfs_priority = pr; 
  return 0;
}

int 
sys_policy(void)
{
  int policy;
  if(argint(0, &policy) < 0)
    panic ("cannot get policy");
  if(policy < 0 || policy > 2)
    return -1;
  sched_type = policy;
  return 0;
}

int
sys_wait(void)
{	
  int* status;
  argptr (0 , (void*)&status ,sizeof(*status));
  return wait(status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int 
sys_memsize(void)
{
   return myproc()->sz;
}


// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
