#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
	char *t="abcde";
	int fd2=6;
	int fd1 = open("a", O_CREATE | O_RDWR );
	printf(1,"%d\n",fd1);
	printf(1,"written %d\n",write(fd1,t,5));
	dup2(fd1,fd2);
	printf(1,"read %d\n",read(fd2,t,5));
	printf(1,"%s",t);
	exit();
}