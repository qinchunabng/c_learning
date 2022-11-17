#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  FILE *fps, *fpd;
  int ch;
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s <src_file> <dest_file>\n", argv[0]);
    exit(1);
  }
  // printf("%s\n", argv[1]);
  fps = fopen(argv[1], "rb");
  if (fps == NULL)
  {
    perror("fopen()");
    exit(1);
  }
  fpd = fopen(argv[2], "wb");
  if (fpd == NULL)
  {
    fclose(fps);
    perror("fopen()");
    exit(1);
  }
  while (1)
  {
    ch = fgetc(fps);
    // printf("%c\n", ch);
    if (ch == EOF)
      break;
    fputc(ch, fpd);
  }
  fclose(fps);
  fclose(fpd);
  return 0;
}