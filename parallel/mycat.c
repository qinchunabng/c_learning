#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
  int fds, fdd = 1;
  char buf[BUFSIZE];
  int len, ret, pos;
  if (argc < 3)
  {
    fprintf(stderr, "Usage...\n");
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
  close(fdd);
  exit(0);
}