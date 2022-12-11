#include <stdlib.h>
#include <stdio.h>

#include "nohead.h"

int list_insert(list **list, const struct score_st *data)
{
  struct node_st *node;
  node = malloc(sizeof(*node));
  if (node == NULL)
  {
    return -1;
  }
  node->data = *data;
  node->next = *list;
  *list = node;
  return 0;
}
void list_show(list *list)
{
  struct node_st *cur = list;
  while (cur && cur->next)
  {
    printf("%d %s %d %d\n", cur->data.id, cur->data.name, cur->data.math, cur->data.chinese);
    cur = cur->next;
  }
}

int list_delete(list **list)
{
  struct node_st *cur;
  if (*list == NULL)
  {
    return -1;
  }
  cur = *list;
  *list = (*list)->next;
  free(cur);
  return 0;
}

struct score_st *list_find(list *list, int id)
{
  struct node_st *cur = list;
  for (; cur != NULL; cur = cur->next)
  {
    if (cur->data.id == id)
    {
      // printf("%d %s %d %d\n", cur->data.id, cur->data.name, cur->data.math, cur->data.chinese);
      return &cur->data;
    }
  }
  return NULL;
}

void list_destroy(list *list)
{
  struct node_st *cur;
  if (list == NULL)
  {
    return;
  }
  for (cur = list; cur != NULL; cur = list)
  {
    list = list->next;
    free(cur);
  }
}