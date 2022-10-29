#include <stdio.h>
#include <stdlib.h>

#include "func.h"

#define M 3
#define N 4

/**
 * int a[M][N] = {...};
 * int *p = *a;
 * int (*q)[N] = a;
 *
 * -> a[i][j]     *(a+i)+j      a[i]+j      p[i]      *p      q[i][j]       *q      q     p+3     q+2
 *
 * -> int         int*          int*        int      int      int         int*    int (*)[]  int*  int (*)[]
 *
 */

void test_n()
{
  printf("%s:N=%d\n", __FUNCTION__, N);
}

void print_2d_array(int *p, int n)
{
  // int a[][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  // int i, j;
  // for (i = 0; i < M; i++)
  // {
  //   for (j = 0; j < N; j++)
  //   {
  //     printf("%d\n", a[i][j]);
  //   }
  // }

  int i;
  for (i = 0; i < n; i++)
  {
    printf("%d\n", p[i]);
  }
}

void print_2d_array1(int (*p)[N], int m, int n)
{
  int i, j;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
    {
      // printf("%4d", p[i][j]);
      printf("%4d", *(*(p + i) + j));
    }
    printf("\n");
  }
}

/**
 * 查找第num个学生的分组
 */
int *find_num(int (*p)[N], int num)
{
  if (num < 0 || num > M - 1)
  {
    return NULL;
  }
  return *(p + num);
}

int add(int a, int b)
{
  return a + b;
}

int sub(int a, int b)
{
  return a - b;
}