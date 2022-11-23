#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FNAME "/tmp/out"
#define BUFSIZE 1023

int main(int argc, char **argv)
{
  int count;
  FILE *flog;
  char buf[BUFSIZE];
  char *ret;
  time_t stamp;
  struct tm *tm;
  count = 0;

  flog = fopen(FNAME, "a+");

  if (flog == NULL)
  {
    perror("fopen()");
    exit(1);
  }

  while ((ret = fgets(buf, BUFSIZE, flog)) != NULL)
  {
    count++;
  }

  while (1)
  {
    time(&stamp);
    tm = localtime(&stamp);
    fprintf(flog, "%-4d%d-%d-%d %02d:%02d:%02d\n", ++count,
            tm->tm_year + 1900, tm->tm_mon | 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);
    fflush(flog);
    sleep(1);
  }
  fclose(flog);
  exit(0);
}