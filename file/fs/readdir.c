#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#define PA "/etc"

int main()
{
  DIR *dp;
  struct dirent *cur;
  dp = opendir(PA);
  if (dp == NULL)
  {
    perror("opendir()");
    exit(1);
  }

  while (1)
  {
    cur = readdir(dp);
    if (cur == NULL)
      break;
    puts(cur->d_name);
  }
  closedir(dp);
  exit(0);
}