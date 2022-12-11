#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define CPS 10
#define BUFSIZE CPS
#define BURST 100

static volatile sig_atomic_t token = 0;

static void alrm_handler(int s)
{
  // alarm(1);
  token++;
  if (token > BURST)
    token = BURST;
}

int main(int argc, char **argv)
{
  int fds, fdd = 1;
  char buf[BUFSIZE];
  int len, ret, pos;
  struct itimerval itv;
  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  signal(SIGALRM, alrm_handler);
  // alarm(1);
  itv.it_interval.tv_sec = 1;
  itv.it_interval.tv_usec = 0;
  itv.it_value.tv_sec = 1;
  itv.it_value.tv_usec = 0;
  if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
  {
    perror("setitimer()");
    exit(1);
  }

  do
  {
    fds = open(argv[1], O_RDONLY);
    if (fds < 0)
    {
      // determine whether is a true error
      if (errno != EINTR)
      {
        perror("open()");
        exit(1);
      }
    }
  } while (fds < 0);

  while (1)
  {
    while (!token <= 0)
      pause();
    token--;

    len = read(fds, buf, BUFSIZE);
    if (len < 0)
    {
      if (errno == EINTR)
        continue;
      perror("read()");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    pos = 0;
    while (len > 0)
    {
      ret = write(fdd, buf + pos, len);
      if (ret < 0)
      {
        if (errno == EINTR)
          continue;
        perror("write()");
        exit(1);
      }
      pos += ret;
      len -= ret;
    }
  }
  close(fds);
  exit(0);
}