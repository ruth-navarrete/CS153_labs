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
	exit();
	return 0; // not reached
}


int sys_exit2(int exit_status)
{
  argint(0,&exit_status);

  exit2(exit_status);
  return 0;  // not reached
}


int
sys_wait(void)
{
  return wait();
}

/*int sys_wait2(void)
{
	int* seven;

	return wait2(seven);	//incomplete
}
*/

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

int sys_waitpid(int pid, int *status, int options)
//sys_waitpid(void)
{
  // used below links for reference
  // https://www.cse.iitd.ernet.in/~sbansal/os/previous_years/2011/xv6_html/syscall_8c.html
//  int pid, options;
//  int *status;

  if(argint(0, &pid) < 0)
    return -1;
  if (argptr(1, (char**)&status, sizeof(status)) < 0)
    return -1;
  if(argint(2, &options) < 0)
    return -1;

  return waitpid(pid, status, options);
}
