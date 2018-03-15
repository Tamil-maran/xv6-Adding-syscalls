#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int
main(void)
{
 struct rtcdate r;
 trace(1);
 printf(0,"aaaa");
 datetime(&r);
 printf(1,"%s\n",r.day );
 ppoint((int*)main);
 trace(0);
 printf(0,"aaaa\n");
 exit();
}