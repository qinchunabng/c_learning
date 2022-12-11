#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include <errno.h>

#define DELIMS " \t\n"

struct cmd_st
{
  glob_t globres;
};

static void prompt()
{
  printf("mysh-0.1$ ");
  fflush(NULL);
}

static void parse(char *line, struct cmd_st *cmd)
{
  int i = 0;
  int res;
  char *tok;
  while (1)
  {
    tok = strsep(&line, DELIMS);
    if (tok == NULL)
      break;
    if (tok[0] == '\0')
      continue;
    // it is not need to append in the first time.
    printf("tok:[%s]\n", tok);
    res = glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &cmd->globres);
    if (res != 0)
    {
      fprintf(stderr, "glob():%s\n", strerror(res));
      // return -2;
    }
    // printf("glob.gl_pathc:%ld\n", cmd->globres.gl_pathc);
    i = 1;
  }
  // return 0;
}

int main()
{
  char *linebuf = NULL;
  size_t linebuf_size = 0;
  struct cmd_st cmd;
  pid_t pid;
  int res;
  while (1)
  {
    prompt();
    if (getline(&linebuf, &linebuf_size, stdin) < 0)
    {
      perror("getline()");
      break;
    }
    // printf("linebuf:[%s]\n", linebuf);
    parse(linebuf, &cmd);
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    if (0)
    {
      //是内部命令
    }
    else
    {
      //是外部命令
      pid = fork();
      if (pid < 0)
      {
        perror("fork()");
        exit(1);
      }
      if (pid == 0)
      {
        // printf("gl_pathv[0]:%s\n", cmd.globres.gl_pathv[0]);
        execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
        perror("execvp()");
        exit(1);
      }
      else
      {
        wait(NULL);
      }
    }
  }
  exit(0);
}