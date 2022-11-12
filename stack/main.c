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