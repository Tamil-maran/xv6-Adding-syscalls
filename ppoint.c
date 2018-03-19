#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int
main(void)
{
	printf(1,"code\n");
	ppoint((int*)main);
	
	printf(1,"\nheap\n");
	int* a = (int*)malloc(sizeof(int));
	ppoint(a);

	printf(1,"\nstack\n");
	int b=5;
	ppoint(&b);
	exit();
}