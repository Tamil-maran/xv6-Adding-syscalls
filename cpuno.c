#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	int a=1;
 for(int i=0; i<3; i++)
 {
 	printf(1,"Cpu no : %d\n",cpuno());
 	sleep(100);
 }
 if(lockcpu(a)==0)
 	printf(1,"Locked to %d\n",a);
 else
 	printf(1,"Lock failed");
 yield();
 for(int i=0; i<3; i++)
 {
 	printf(1,"Cpu no : %d\n",cpuno());
 	sleep(100);
 }
 unlockcpu();
 printf(1,"Unlocked\n");
 for(int i=0; i<3; i++)
 {
 	printf(1,"Cpu no : %d\n",cpuno());
 	sleep(100);
 }
 exit();
}