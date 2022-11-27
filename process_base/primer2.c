#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define N 3

int main()
{
  int i, j, n, flag;
  pid_t pid;
  int status;
  for (n = 0; n < N; n++)
  {
    pid = fork();
    if (pid < 0)
    {
      perror("fork()");
      exit(1);
    }
    if (pid == 0)
    {
      for (i = LEFT + n; i <= RIGHT; i += N)
      {

        flag = 1;
        for (j = 2; j < i / 2; j++)
        {
          if (i % j == 0)
          {
            // printf("%d %d\n", i, j);
            flag = 0;
            break;
          }
        }
        if (flag)
          printf("%d is a primer.\n", i);
        // sleep(1000);
      }
      exit(0);
    }
  }

  // waiting for releasing children's resource
  for (i = 0; i < N; i++)
  {
    pid = wait(&status);
    printf("pid=%d\n", pid);
  }
  // sleep(1000);
  exit(0);
}