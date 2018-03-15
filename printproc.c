#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int
main(void)
{
	printproc(getpid());
	exit();
}