#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
  FILE *fp;
  fp = fopen("tmp", "r");
  if (fp == NULL)
  {
    // perror("fopen()");
    fprintf(stderr, "fopen(): %s\n", strerror(errno));
    exit(1);
  }
  puts("OK");
  fclose(fp);
  return 0;
}