#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#define FNAME "/tmp/out"

static FILE *fp;

static int daemonize()
{
  int fd;
  pid_t pid;
  pid = fork();

  if (pid < 0)
  {
    // perror("fork()");
    return -1;
  }

  if (pid > 0)
  {
    exit(0);
  }

  fd = open("/dev/null", O_RDWR);
  if (fd < 0)
  {
    // perror("open()");
    syslog(LOG_ERR, "fopen():%s", strerror(errno));
    return -1;
  }

  syslog(LOG_INFO, "%s was opened.", FNAME);

  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);

  if (fd > 2)
  {
    close(fd);
  }
  setsid();
  chdir("/");
  // umask(0);
}

static void daemon_exit(int s)
{
  fclose(fp);
  closelog();
  exit(0);
}

int main()
{
  int i;
  struct sigaction sa;

  sa.sa_handler = daemon_exit;
  sigemptyset(&sa.sa_mask);
  sigaddset(&sa.sa_mask, SIGQUIT);
  sigaddset(&sa.sa_mask, SIGINT);
  sigaddset(&sa.sa_mask, SIGTERM);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGQUIT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);
  // signal(SIGINT, daemon_exit);
  // signal(SIGQUIT, daemon_exit);
  // signal(SIGTERM, daemon_exit);

  openlog("mydaemon", LOG_PID, LOG_DAEMON);

  if (daemonize() < 0)
  {
    syslog(LOG_ERR, "daemonzie() failed!");
    exit(1);
  }
  else
  {
    syslog(LOG_INFO, "daemonize() succeeded!");
  }

  fp = fopen(FNAME, "w");
  if (fp == NULL)
  {
    perror("fopen()");
    exit(1);
  }

  for (i = 0;; i++)
  {
    fprintf(fp, "%d\n", i);
    fflush(fp);
    syslog(LOG_DEBUG, "%d is printed.", i);
    sleep(1);
  }

  fclose(fp);
  exit(0);
}