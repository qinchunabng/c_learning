#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define TIMESTRSIZE 1024
#define FMTSTRSIZE 1024

int main(int argc, char *argv[])
{
  time_t stamp;
  struct tm *tm;
  char timestr[TIMESTRSIZE];
  int c;
  char fmtstr[FMTSTRSIZE];
  FILE *fp;

  fmtstr[0] = '\0';
  fp = stdout;

  stamp = time(NULL);
  tm = localtime(&stamp);

  if (tm == NULL)
  {
    fprintf(stderr, "localtime() error.\n");
    exit(1);
  }

  while (1)
  {
    c = getopt(argc, argv, "-H:MSy:md");
    if (c < 0)
      break;
    switch (c)
    {
    case 1:
      fp = fopen(argv[optind - 1], "w");
      if (fp == NULL)
      {
        perror("fopen()");
        // exit(1);
        fp = stdout;
      }
      break;
    case 'H':
      if (strcmp(optarg, "12") == 0)
      {
        strncat(fmtstr, "%I(%P) ", FMTSTRSIZE);
      }
      else if (strcmp(optarg, "24") == 0)
      {
        strncat(fmtstr, "%H ", FMTSTRSIZE);
      }
      else
      {
        fprintf(stderr, "Invalid argument of -H.");
        exit(1);
      }

      break;
    case 'M':
      strncat(fmtstr, "%M ", FMTSTRSIZE);
      break;
    case 'S':
      strncat(fmtstr, "%S ", FMTSTRSIZE);
      break;
    case 'y':
      if (strcmp(optarg, "2") == 0)
      {
        strncat(fmtstr, "%y ", FMTSTRSIZE);
      }
      else if (strcmp(optarg, "4") == 0)
      {
        strncat(fmtstr, "%Y ", FMTSTRSIZE);
      }
      else
      {
        fprintf(stderr, "Invalid argument of -y.");
        exit(1);
      }
      break;
    case 'm':
      strncat(fmtstr, "%m ", FMTSTRSIZE);
      break;
    case 'd':
      strncat(fmtstr, "%d ", FMTSTRSIZE);
      break;
    default:
      break;
    }
  }

  // puts(fmtstr);
  strftime(timestr, TIMESTRSIZE, fmtstr, tm);
  fputs(timestr, fp);

  if (fp != stdout)
    fclose(fp);
  exit(0);
}