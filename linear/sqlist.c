#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

sqlist *sqlist_create()
{
  sqlist *me = NULL;
  me = malloc(sizeof(*me));
  if (me == NULL)
    return NULL;
  me->last = -1;
  return me;
}
void sqlist_create1(sqlist **ptr)
{
  *ptr = malloc(sizeof(**ptr));
  if (*ptr == NULL)
  {
    return;
  }
  (*ptr)->last = -1;
}
void sqlist_display(sqlist *p)
{
  int i;
  if (sqlist_isempty(p) == 0)
  {
    return;
  }
  for (i = 0; i <= p->last; i++)
  {
    printf("%d\t", p->data[i]);
  }
  printf("\n");
}
int sqlist_insert(sqlist *p, int i, datatype *d)
{
  int j;
  if (p->last == DATASIZE - 1)
  {
    return -1;
  }
  if (i < 0 || i > p->last + 1)
  {
    return -2;
  }
  for (j = p->last; i <= j; j--)
  {
    p->data[j + 1] = p->data[j];
  }
  p->data[i] = *d;
  p->last++;
  return 0;
}
int sqlist_delete(sqlist *p, int i)
{
  int j;
  if (i < 0 || i > p->last)
  {
    return -1;
  }
  for (j = i + 1; j < p->last; j++)
  {
    p->data[j - 1] = p->data[j];
  }
  p->last--;
  return 0;
}
int sqlist_find(sqlist *p, datatype *d)
{
  int i;
  if (sqlist_isempty(p) == 0)
  {
    return -1;
  }
  for (i = 0; i <= p->last; i++)
  {
    if (p->data[i] == *d)
    {
      return i;
    }
  }
  return -2;
}
int sqlist_isempty(sqlist *p)
{
  if (p->last == -1)
  {
    return 0;
  }
  return -1;
}
int sqlist_setempty(sqlist *p)
{
  p->last = -1;
  return 0;
}

int sqlist_getlen(sqlist *p)
{
  return p->last + 1;
}

int sqlist_union(sqlist *s1, sqlist *s2)
{
  int i;
  for (i = 0; i <= s2->last; i++)
  {
    if (sqlist_find(s1, &s2->data[i]) < 0)
    {
      sqlist_insert(s1, 0, &s2->data[i]);
    }
  }
}

int sqlist_destroy(sqlist *p)
{
  free(p);
  return 0;
}
