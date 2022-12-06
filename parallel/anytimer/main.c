#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "anytimer.h"
#include <string.h>

int main()
{
  int job1, job2, job3;
  puts("Begin!");
  job1 = at_addjob(5, f1, "aaa");
  if (job1 < 0)
  {
    fprintf(stderr, "at_addjob(): %s\n", strerror(-job1));
    exit(1);
  }
  job2 = at_addjob(2, f2, "aaa");
  job3 = at_addjob(7, f1, "aaa");
  puts("End!");

  while (1)
  {
    write(1, ".", 1);
    sleep(1);
  }
  exit(0);
}