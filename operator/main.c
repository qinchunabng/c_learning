#include <stdio.h>
#include <stdlib.h>

/*
 * 将n的第i位置为1
 * i从0开始
 */
int set1(int n, int i)
{
  if (i < 0)
  {
    return n;
  }
  return n | 1 << i;
}

/**
 * 将n的第i置为0
 * i从0开始
 */
int set0(int n, int i)
{
  if (i < 0)
  {
    return n;
  }
  return n & ~(1 << i);
}

/**
 * 检测n的第i位的值
 * i从0开始
 */
int testn(int n, int i)
{
  if (i < 0)
  {
    return -1;
  }
  return n & 1 << i ? 1 : 0;
}

/**
 * 获取n从起始位from到to（不包含）之间的比特位
 */
int getbits(int n, int from, int to)
{
  int mask;
  if (from < 0 || to <= from)
  {
    return -1;
  }
  n = n >> from;
  mask = (1 << (to - from)) - 1;
  return n & mask;
}

int main(void)
{
  int i = 7;
  int j = 15;
  int n = 13;

  printf("将%d的第%d位置为1结果：%d\n", i, 3, set1(i, 3));
  printf("将%d的第%d位置为0结果：%d\n", j, 3, set0(j, 3));

  printf("%d的第%d位：%d\n", i, 3, testn(i, 3));
  printf("%d的第%d位：%d\n", j, 3, testn(j, 3));

  printf("%d的第%d位至第%d位比特位数值: %d", n, 0, 2, getbits(n, 0, 3));
  exit(0);
}
