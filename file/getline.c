#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  FILE *fp;
  char *line = NULL;
  size_t n = 0;
  if (argc < 2)
  {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    perror("fopen()");
    exit(1);
  }
  while (1)
  {
    if (getline(&line, &n, fp) < 0)
      break;
    printf("%d\n", n);
    printf("%s\n", line);
  }

  free(line);
  fclose(fp);
  exit(0);
}