#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
  int fds, fdd;
  char buf[BUFSIZE];
  int len, ret, pos = 0;
  if (argc < 3)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }
  fds = open(argv[1], O_RDONLY);
  if (fds < 0)
  {
    perror("open()");
    exit(1);
  }
  fdd = open(argv[2], O_WRONLY | O_CREAT, 0600);
  if (fdd < 0)
  {
    close(fds);
    perror("open()");
    exit(1);
  }

  while (1)
  {
    len = read(fds, buf, BUFSIZE);
    if (len < 0)
    {
      perror("read()");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    while (len > 0)
    {
      ret = write(fdd, buf + pos, len);
      if (ret < 0)
      {
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