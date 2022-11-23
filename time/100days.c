#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TIMESTRSIZE 50

int main()
{
  time_t stamp;
  struct tm *tm;
  char timestr[TIMESTRSIZE];
  stamp = time(NULL);
  tm = localtime(&stamp);

  if (tm == NULL)
  {
    fprintf(stderr, "localtime() error.\n");
    exit(1);
  }

  strftime(timestr, TIMESTRSIZE, "Now:%Y-%m-%d", tm);
  puts(timestr);

  tm->tm_mday += 100;
  if (mktime(tm) < 0)
  {
    fprintf(stderr, "mktime() error.\n");
    exit(1);
  }

  strftime(timestr, TIMESTRSIZE, "100 days later:%Y-%m-%d", tm);
  puts(timestr);
  exit(0);
}