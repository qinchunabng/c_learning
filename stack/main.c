#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define MAXSIZE 32

struct score_st
{
  int id;
  char name[MAXSIZE];
  int math;
  int chinese;
};

void print_s(const void *r)
{
  const struct score_st *ptr = r;
  printf("%d %s %d %d\n", ptr->id, ptr->name, ptr->chinese, ptr->math);
}

/**
 * 1.静态库
 * 1) libxxx.a
 *    xx指代库名
 * 2) ar -cr libxxx.a yyy.o
 *    将.o文件打包为静态库文件
 * 3) 发布到
 *    /usr/local/include
 *    /usr/local/lib
 *    头文件放到/usr/local/include目录，静态库文件放到/usr/local/lib
 * 4) gcc -L/user/local/lib -o main main.o -lxx
 *    -l 参数必须在最后，有依赖
 *
 * 2.动态库
 * 1) libxx.so
 *    动态库以.so结尾
 *
 * 2) gcc -shared -fpic -o libxx.so yyy.c
 *    将.c打包为动态库
 * 3) 发布到
 *    /usr/local/include
 *    /usr/local/lib
 *    头文件放到/usr/local/include目录，静态库文件放到/usr/local/lib
 *    非root用户发布
 *    cp xx.so ~/lib
 *    export LD_LIBRARY_PATH=~/lib
 * 4) 在/etc/ld.so.conf中添加路径
 *    /sbin/config 重读/etc/ld.so.conf
 *
 *
 * 3. 查看动态库依赖
 * ldd - print shared library dependencies
 *
 */
int main(void)
{
  int i, ret;
  STACK *st;
  struct score_st tmp;
  st = stack_create(sizeof(struct score_st));
  if (st == NULL)
    exit(1);
  for (i = 0; i < 7; i++)
  {
    tmp.id = i;
    snprintf(tmp.name, MAXSIZE, "stu%d", i);
    tmp.math = rand() % 100;
    tmp.chinese = rand() % 100;
    stack_push(st, &tmp);
  }

  ;
  if (stack_top(st, &tmp) == 0)
    print_s(&tmp);

  while (1)
  {
    ret = stack_pop(st, &tmp);
    if (ret != 0)
    {
      break;
    }
    print_s(&tmp);
  }
  if (stack_isempty(st))
    printf("Stack is empty now.\n");
  stack_destroy(st);
  exit(0);
}