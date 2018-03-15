#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int
main(void)
{
 struct rtcdate r; 
 datetime(&r);
 printf(1,"GMT %d:%d:%d %d/%d/%d\n",r.hour,r.minute,r.second,r.day,r.month,r.year);
 exit();
}