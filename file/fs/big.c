#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  int fd;
  int ret;
  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }
  fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if (fd < 0)
  {
    perror("open()");
    exit(1);
  }

  // seek 5gb from the beginning of the file
  ret = lseek(fd, 1024L * 1024L * 1024L * 1L - 1L, SEEK_SET);
  if (ret < 0)
  {
    close(fd);
    perror("lseek()");
    exit(1);
  }
  ret = write(fd, "", 1);
  if (ret < 0)
  {
    close(fd);
    perror("write()");
    exit(1);
  }

  close(fd);
  exit(0);
}