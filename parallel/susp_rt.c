#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MYRTSIG (SIGRTMIN + 6)

static void mysig_handler(int s)
{
  write(1, "!", 1);
}

int main()
{
  int i, j;
  sigset_t set, oset, saveset, tmpset;
  // signal(SIGINT, SIG_IGN);
  signal(MYRTSIG, mysig_handler);
  sigemptyset(&set);
  sigaddset(&set, MYRTSIG);
  sigprocmask(SIG_UNBLOCK, &set, &saveset);
  sigprocmask(SIG_BLOCK, &set, &oset);8
  for (j = 0; j < 1000; j++)
  {
    // sigprocmask(SIG_BLOCK, &set, &oset);
    for (i = 0; i < 5; i++)
    {
      write(1, "*", 1);
      sleep(1);
    }
    write(1, "\n", 1);

    sigsuspend(&oset);
    // sigprocmask(SIG_SETMASK, &oset, &tmpset);
    // pause();
    // sigprocmask(SIG_SETMASK, &tmpset, NULL);
  }
  sigprocmask(SIG_SETMASK, &saveset, NULL);
  exit(0);
}