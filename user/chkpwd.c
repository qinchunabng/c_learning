#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>
#include <crypt.h>

int main(int argc, char **argv)
{
  char *passwd, *crypt_pwd;
  struct spwd *shadowline;

  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  passwd = getpass("Password:");
  if (passwd == NULL)
  {
    perror("getpass(0");
    exit(1);
  }

  shadowline = getspnam(argv[1]);
  if (shadowline == NULL)
  {
    fprintf(stderr, "getspnam(name) failed, name: %s\n", argv[1]);
    exit(1);
  }

  printf("sp_namp:%s\tsp_pwdp:%s\n", passwd, shadowline->sp_pwdp);
  crypt_pwd = crypt(passwd, shadowline->sp_pwdp);
  if (crypt_pwd == NULL)
  {
    fprintf(stderr, "crypt() error.\n");
    exit(1);
  }

  if (strcmp(crypt_pwd, shadowline->sp_pwdp) == 0)
  {
    puts("ok!");
  }
  else
  {
    puts("failed!");
  }
  exit(0);
}