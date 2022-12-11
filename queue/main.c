#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define MAXSIZE 32

struct score_st
{
  int id;
  char name[MAXSIZE];
  int math;
  int chinese;
};

void print_s(void *r)
{
  struct score_st *ptr = r;
  printf("%d %s %d %d\n", ptr->id, ptr->name, ptr->chinese, ptr->math);
}

int main(void)
{
  QUEUE *q;
  int i, ret;
  struct score_st tmp;
  q = queue_create(sizeof(struct score_st));

  for (i = 0; i < 7; i++)
  {
    tmp.id = i;
    snprintf(tmp.name, MAXSIZE, "stu%d", i);
    tmp.chinese = rand() % 100;
    tmp.math = rand() % 100;
    queue_en(q, &tmp);
  }

  while (1)
  {
    ret = queue_de(q, &tmp);
    if (ret != 0)
    {
      exit(1);
    }
    print_s(&tmp);
  }
  queue_destroy(q);
  exit(0);
}