#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  struct passwd *pwdline;
  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  errno = 0;
  pwdline = getpwuid(atoi(argv[1]));
  if (pwdline == NULL && errno != 0)
  {
    perror("getpwuid()");
    exit(1);
  }
  puts(pwdline->pw_name);

  exit(0);
}