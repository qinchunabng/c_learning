#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PATHSIZE 1024

static int path_noloop(const char *path)
{
  char *pos;
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  pos = strrchr(path, '/');
  if (pos == NULL)
  {
    exit(1);
  }
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  // printf("%s %d %d\n", pos + 1, strcmp(pos + 1, "."), strcmp(pos + 1, ".."));
  if (strcmp(pos + 1, ".") == 0 || strcmp(pos + 1, "..") == 0)
  {
    return 0;
  }
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  return 1;
}

static int errfuc(const char *epath, int eerrno)
{
  printf("%s: %s\n", epath, strerror(eerrno));
  return 0;
}

// determine if the path ends up with a slash
static int end_slash(const char *path)
{
  char *pos;
  pos = strrchr(path, '/');
  if (pos == NULL)
  {
    return -1;
  }
  if (strcmp(pos, "/") == 0)
  {
    return 0;
  }
  return 1;
}

static int64_t mydu(const char *path)
{
  static struct stat stat_res;
  int ret;
  char nextpath[PATHSIZE] = "";
  static glob_t glob_res;
  int i;
  int64_t sum = 0;
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  printf("path: %s\n", path);
  ret = lstat(path, &stat_res);
  if (ret < 0)
  {
    perror("lstat()");
    exit(1);
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  // if it is not a directory
  if (!S_ISDIR(stat_res.st_mode))
  {
    return stat_res.st_blocks;
  }

  sum += stat_res.st_blocks;
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  // if it is a directory.
  strncpy(nextpath, path, PATHSIZE);
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  if (end_slash(nextpath) != 0)
  {
    strncat(nextpath, "/", PATHSIZE);
  }
  strncat(nextpath, "*", PATHSIZE);
  // printf("%s:%d: nextpath:%s\n", __FUNCTION__, __LINE__, nextpath);
  // printf("nextpath: %p\n", nextpath);
  // printf("&glob_res: %p\n", &glob_res);
  ret = glob(nextpath, 0, errfuc, &glob_res);
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  if (ret < 0)
  {
    perror("glob()");
    exit(1);
  }

  for (i = 0; i < glob_res.gl_pathc; i++)
  {
    if (path_noloop(glob_res.gl_pathv[i]))
    {
      sum += mydu(glob_res.gl_pathv[i]);
      // printf("%s:%d: path:%s\n", __FUNCTION__, __LINE__, glob_res.gl_pathv[i]);
    }
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  // getting invisible files
  strncpy(nextpath, path, PATHSIZE);
  if (end_slash(nextpath) != 0)
  {
    strncat(nextpath, "/", PATHSIZE);
  }
  strncat(nextpath, ".*", PATHSIZE);
  ret = glob(nextpath, 0, errfuc, &glob_res);
  if (ret < 0)
  {
    perror("glob()");
    exit(1);
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  for (i = 0; i < glob_res.gl_pathc; i++)
  {
    if (path_noloop(glob_res.gl_pathv[i]))
    {
      sum += mydu(glob_res.gl_pathv[i]);
      // printf("%s:%d: path:%s\n", __FUNCTION__, __LINE__, glob_res.gl_pathv[i]);
    }
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  globfree(&glob_res);
  return sum;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  // printf("%s\n", strrchr(argv[1], '/'));

  printf("%ld\n", mydu(argv[1]) / 2);
  exit(0);
}