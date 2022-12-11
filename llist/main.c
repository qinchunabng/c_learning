#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE 32

struct score_st
{
  int id;
  char name[NAMESIZE];
  int math;
  int chinese;
};

void print_score(const void *record)
{
  const struct score_st *r = record;
  printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

static int id_cmp(const void *key, const void *record)
{
  const int *k = key;
  const struct score_st *r = record;
  return (*k - r->id);
}

static int name_cmp(const void *key, const void *record)
{
  const char *k = key;
  const struct score_st *r = record;
  return strcmp(k, r->name);
}

int main(void)
{
  int i, id = 3, ret;
  struct score_st tmp, *data;
  LLIST *handler;
  char *name = "stu6";
  handler = llist_create(sizeof(struct score_st));

  if (handler == NULL)
  {
    exit(1);
  }

  for (i = 0; i < 7; i++)
  {
    tmp.id = i;
    snprintf(tmp.name, NAMESIZE, "stu%d", i);
    tmp.math = rand() % 100;
    tmp.chinese = rand() % 100;
    llist_insert(handler, &tmp, LLIST_BACKWARD);
  }

  llist_travel(handler, print_score);

  printf("\n\n");

  data = llist_find(handler, name, name_cmp);
  if (data == NULL)
  {
    printf("Cannot find.");
  }
  else
  {
    print_score(data);
  }
#if 0
  ret = llist_delete(handler, &id, id_cmp);
  if (ret)
  {
    printf("llist_delete failed!\n");
  }
  llist_travel(handler, print_score);

  data = llist_find(handler, &id, id_cmp);
  if (data == NULL)
  {
    printf("Cannot find.");
  }
  else
  {
    print_score(data);
  }
#endif
  llist_destroy(handler);
  exit(0);
}
