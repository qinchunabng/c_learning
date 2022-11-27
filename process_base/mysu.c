#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int ret;
  if (argc < 3)
  {
    fprintf(stderr, "Usage....\n");
    exit(1);
  }

  pid = fork();
  if (pid < 0)
  {
    perror("fork()");
    exit(1);
  }

  if (pid == 0)
  {
    // child process
    ret = setuid(atoi(argv[1]));
    if (ret < 0)
    {
      perror("setuid()");
      exit(1);
    }
    execvp(argv[2], argv + 2);
    perror("execvp()");
    exit(1);
  }
  else
  {
    // parent process
  }
  wait(NULL);
  exit(0);
}