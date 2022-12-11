#include <stdlib.h>
#include <stdio.h>

#if 0
void func(int *p, int n)
{
  p = malloc(n);
  if (p == NULL)
    exit(1);
  return;
}
#else
void func(int **p, int n)
{
  *p = malloc(n);
  if (*p == NULL)
    exit(1);
  return;
}
#endif

int main(void)
{
#if 0
  int *p = NULL;
  p = malloc(sizeof(int));
  if (p == NULL)
    printf("malloc() error!\n");
  *p = 10;
  printf("%d\n", *p);
  free(p);
#endif

#if 0
  int *p;
  int num = 5;
  p = malloc(sizeof(int) * num);
  int i;
  for (i = 0; i < num; i++)
  {
    scanf("%d", &p[i]);
  }
  for (i = 0; i < num; i++)
  {
    printf("%d\n", p[i]);
  }
  free(p);
#endif

  int num = 100;
  int *p = NULL;
  func(&p, num);
  free(p);
  exit(0);
}