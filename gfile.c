#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main()
{
  int fd = open("a", O_CREATE | O_RDWR );
  int pid,pfd=6;
  char *t="bcdef";
  pid=fork();
  if(pid)
  {
  	gfile(pid,fd,pfd);
  	printf(1,"%d",write(fd,t,5));
  	close(fd);
  }
  else
  {
  	sleep(20);
  	char r[5];
  	printf(1,"%d",read(pfd,r,5));
  	printf(1,"%s\n",r );
  	close(pfd);
  }
  exit();
}