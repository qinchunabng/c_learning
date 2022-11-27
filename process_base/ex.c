#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;

  pid = fork();
  if (pid < 0)
  {
    perror("fork()");
    exit(0);
  }

  if (pid == 0)
  {
    // child process
    execl("/bin/date", "date", "+%s", NULL);
    perror("execl()");
    exit(1);
  }

  // waiting for child process
  wait(NULL);
  exit(0);
}