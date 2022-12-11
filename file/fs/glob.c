#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

#define PAT "/etc/a*.conf"

static int errfunc_(const char *epath, int eerrno)
{
  puts(epath);
  fprintf(stderr, "ERROR MSG:%s\n", strerror(eerrno));
  return 0;
}

int main(int argc, char *argv[])
{
  glob_t glob_res;
  int err, i;
  err = glob(PAT, 0, errfunc_, &glob_res);
  if (err)
  {
    fprintf(stderr, "Error code: %d\n", err);
    exit(1);
  }

  for (i = 0; i < glob_res.gl_pathc; i++)
  {
    puts(glob_res.gl_pathv[i]);
  }

  globfree(&glob_res);
  exit(0);
}