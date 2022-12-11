#include <stdio.h>
#include <stdlib.h>

#include "func.h"

/**
 * int a[N] = {1,2,3,4,5,6};
 * int *p = a;
 *
 * -> a   *a    a[0]    &a[3]   p[i]    p   *p    p+1
 *
 *-> int* int   int     int*    int     int* int  int*
 *
 */

int func(int n)
{
  if (n == 1 || n == 0)
  {
    return 1;
  }
  return n * func(n - 1);
}

/**
 * 斐波那契数列函数
 */
int fab(int n)
{
  if (n < 1)
    return -1;
  if (n == 1 || n == 2)
    return 1;
  return fab(n - 1) + fab(n - 2);
}

/**
 * print array
 * p: a pointer of array
 * n: the length of array
 */
void print_arr(int p[], int n)
{
  int i;
  if (p == NULL)
  {
    fprintf(stderr, "stderr: pointer p is NULL.\n");
    return;
  }
  printf("%s:%d\n", __FUNCTION__, sizeof(p));
  for (i = 0; i < n; i++)
  {
    printf("%d\n", *(p + i));
  }
}

/**
 * reverse an array
 */
void reverse(int *p, int n)
{
  int m = n / 2;
  int tmp, i, j;
  for (i = 0; i < m; i++)
  {
    tmp = p[i];
    j = n - 1 - i;
    p[i] = p[j];
    p[j] = tmp;
  }
}

int main(void)
{
  int a = 3, b = 5;
  int i;
  int ret;
  //函数指针声明
  int (*p)(int, int);
  //函数指针数组
  int (*funcp[2])(int, int);
  // assign function pointer p
  // p point to a function
  p = add;
  // p = &add;

  // call function pointer
  ret = p(a, b);
  printf("%d\n", ret);

  funcp[0] = add;
  funcp[1] = sub;

  for (i = 0; i < 2; i++)
  {
    ret = funcp[i](a, b);
    printf("%d\n", ret);
  }
#if 0
  // printf("%s:N=%d\n", __FUNCTION__, N);
  // test_n();
  int a[][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int *res;
  // print_2d_array(a[0], M * N);
  // print_2d_array(&a[0][0], M * N);

  // print_2d_array1(a, M, N);

  res = find_num(a, 3);
  print_arr(res, N);
#endif
#if 0
  int a[] = {1, 2, 3, 4, 5, 6};
  printf("%s:%d\n", __FUNCTION__, sizeof(a));
  print_arr(a, sizeof(a) / sizeof(a[0]));

  reverse(a, sizeof(a) / sizeof(*a));

  print_arr(a, sizeof(a) / sizeof(a[0]));

#endif
  // int n;
  // n = fab(5);
  // printf("%d\n", n);
#if 0
  int n, res;
  scanf("%d", &n);

  res = func(n);
  printf("%d!=%d\n", n, res);
#endif
  exit(0);
}