#include <stdlib.h>
#include <stdio.h>

#include "linklist.h"

list *list_create()
{
  list *me;
  me = malloc(sizeof(*me));
  if (me == NULL)
  {
    return NULL;
  }
  me->next = NULL;
  return me;
}

int list_insert_at(list *me, int i, datatype *data)
{
  int j = 0;
  list *node = me;
  list *newnode = NULL;
  if (i < 0)
  {
    return -1;
  }
  for (; j < i; j++)
  {
    node = node->next;
    if (node == NULL)
    {
      return -2;
    }
  }
  newnode = malloc(sizeof(*newnode));
  if (newnode == NULL)
  {
    return -3;
  }
  newnode->data = *data;
  newnode->next = node->next;
  node->next = newnode;
  return 0;
}

int list_order_insert(list *me, datatype *data)
{
  list *node = me, *newnode;
  while (node->next && node->next->data < *data)
  {
    node = node->next;
  }
  newnode = malloc(sizeof(*newnode));
  if (newnode == NULL)
  {
    return -1;
  }
  newnode->data = *data;
  newnode->next = node->next;
  node->next = newnode;
  return 0;
}

int list_delete_at(list *me, int i, datatype *data)
{
  list *node = me, *p;
  int j = 0;
  *data = -1;
  if (i < 0)
  {
    return -1;
  }
  while (j < i && node)
  {
    node = node->next;
    j++;
  }
  if (node)
  {
    p = node->next;
    node->next = p->next;
    *data = p->data;
    free(p);
    p = NULL;
    return 0;
  }
  return -2;
}

/**
 * delete a item from the list
 */
int list_delete(list *me, datatype *data)
{
  list *node = me, *p;
  while (node->next && node->next->data != *data)
  {
    node = node->next;
  }

  if (node->next)
  {
    p = node->next;
    node->next = node->next->next;
    free(p);
    p = NULL;
    return 0;
  }
  return -1;
}

int list_isempty(list *me)
{
  if (me->next == NULL)
  {
    return 0;
  }
  return 1;
}

void list_destroy(list *me)
{
  list *node = me->next;
  list *next;
  for (; node != NULL; node = next)
  {
    next = node->next;
    free(node);
  }
  free(me);
}

void list_display(list *me)
{
  list *node = me->next;
  if (list_isempty(me) == 0)
  {
    return;
  }
  while (node != NULL)
  {
    printf("%d ", node->data);
    node = node->next;
  }
  printf("\n");
  return;
}