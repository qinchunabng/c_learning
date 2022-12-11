#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "mytbf.h"

#define CPS 10
#define BUFSIZE 1024
#define BURST 100

int main(int argc, char **argv)
{
  int fds, fdd = 1;
  char buf[BUFSIZE];
  int len, ret, pos;
  mytbf_t *tbf = NULL;
  int size;
  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  tbf = mytbf_init(CPS, BURST);
  if (tbf == NULL)
  {
    fprintf(stderr, "mytbf_init() failed!\n");
    exit(1);
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
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

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  while (1)
  {
    size = mytbf_fetch(tbf, BUFSIZE);
    if (size < 0)
    {
      fprintf(stderr, "mytbf_fetch(): %s\n", strerror(-size));
      exit(1);
    }
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    while ((len = read(fds, buf, size)) < 0)
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
    if (size - len > 0)
    {
      mytbf_returntoken(tbf, size - len);
    }
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
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
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  close(fds);
  mytbf_destory(tbf);
  exit(0);
}