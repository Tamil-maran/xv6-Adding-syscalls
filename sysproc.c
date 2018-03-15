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
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
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

int 
sys_listproc(void)
{
  listproc();
  return 0;
}

int
sys_dumplog(void)
{
  dumplog();
  return 0;
}

int 
sys_shutdown(void)
{
  cprintf("calling sys_halt\n");
  char *p = "Shutdown";
  for( ; *p; p++)
    outb(0x8900, *p);
  return 0;
}

int
sys_trace(void)
{
  int n;
  struct proc *p = myproc();
  argint(0, &n);
  if(n)
    {
      cprintf("\nTrace turned on for %s(pid: %d) \n",p->name,p->pid);
      p->trace=1;
      p->totalcalls=0;
    }
    else
    {
      cprintf("\nTrace turned off for %s(pid: %d) \n",p->name,p->pid);
      p->trace=0;
      p->totalcalls=0;
    }
  return 0;
}

int
sys_datetime(void)
{
  char *c;
  argptr(0,&c,sizeof(struct rtcdate));
  cmostime((struct rtcdate*)c);

  return 0;
}

int
sys_ppoint(void)
{
  char* c;
  argptr(0,&c,sizeof(int*));
  cprintf("Virtual address %p\n",c);
  c = (char*)walkpgdir(myproc()->pgdir, (void*)c, 0);
  cprintf("Physical address %p\n",c);
  return 0;
}

int
sys_extend_as(void)
{
  int newsz;
  argint(0,&newsz);
  int n = growproc(newsz);
  if(n==-1)
    cprintf("Allocation failed\n");
  else if(n==0)
    cprintf("Old size : %d\nNew size %d\n",myproc()->sz,myproc()->sz+newsz);
  return 0;
}


int 
sys_yield(void)
{
  yield();
  return 0;
}

int
sys_alarm(void)
{
  int ticks;
  void (*handler)();

  if(argint(0, &ticks) < 0)
    return -1;
  if(argptr(1, (char**)&handler, 1) < 0)
    return -1;
  struct proc* p = myproc();
  p->tot_ticks = ticks;
  p->rem_ticks = ticks;
  p->handler = handler;
  return 0;
}

int
sys_printproc(void)
{
  int pid,count=0,i;
  if(argint(0, &pid) < 0)
    return -1;
  char* st[] = { "UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE" };
  struct proc* p = getproc(pid);
  cprintf("Name : %s | PID : %d\n",p->name,p->pid);
  cprintf("Size : %d\n",p->sz);
  cprintf("Page directory location : %p\n",(uint*)p->pgdir);
  cprintf("Parent : %s | PID : %d\n",p->parent->name,p->parent->pid);
  cprintf("State : %s\n",st[p->state]);
  cprintf("Context\n");
  cprintf("   edi : %p\n",p->context->edi);
  cprintf("   esi : %p\n",p->context->esi);
  cprintf("   ebx : %p\n",p->context->ebx);
  cprintf("   ebp : %p\n",p->context->ebp);
  cprintf("   eip : %p\n",p->context->eip);
  for(i=0; i<NOFILE; i++)
  if(p->ofile[i]!=0)
    count++;
  cprintf("Number of files open : %d\n",count);
  cprintf("Launch time : %d:%d:%d \n",p->start->hour,p->start->minute,p->start->second);
  cprintf("Trace : %d\n",p->trace);
  return 0;
}