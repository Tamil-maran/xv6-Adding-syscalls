#include "types.h"
#include "stat.h"
#include "user.h"

void fun()
{
  printf(1, "abc\n");
}

int main()
{
  printf(1, "Alarm function\n");
  alarm(100, fun);
  while(1);
  exit();
}

