#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
 trace(1);
 printf(0,"aaaa");
 trace(0);
 printf(0,"aaaa\n");
 trace(1);
 fork();
 printf(0,"aaaa\n");
 trace(1);
 exit();
}