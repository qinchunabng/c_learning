#include <stdlib.h>
#include <stdio.h>

#define JOSE_NR 8

struct node_st
{
  int data;
  struct node_st *next;
};

struct node_st *jose_create(int n)
{
  struct node_st *list, *node, *cur;
  int i = 1;
  list = malloc(sizeof(*list));
  if (list == NULL)
  {
    return NULL;
  }
  list->data = i;
  i++;
  list->next = list;
  cur = list;

  for (; i <= n; i++)
  {
    node = malloc(sizeof(*node));
    if (node == NULL)
    {
      return NULL;
    }
    node->data = i;
    node->next = list;
    cur->next = node;
    cur = node;
  }
  return list;
}

void jose_show(struct node_st *list)
{
  struct node_st *cur = list;
  for (; cur->next != list; cur = cur->next)
  {
    printf("%d ", cur->data);
  }
  printf("%d\n", cur->data);
}

void jose_kill(struct node_st *list, int n)
{
  struct node_st *cur = list, *node;
  int i = 1;
  while (cur != cur->next)
  {
    while (i < n)
    {
      node = cur;
      cur = cur->next;
      i++;
    }

    printf("%d\n", cur->data);
    node->next = cur->next;
    free(cur);

    cur = node->next;
    i = 1;
  }
  printf("\n");
}

int main(void)
{
  struct node_st *list;
  list = jose_create(JOSE_NR);
  jose_show(list);
  jose_kill(list, 3);
  exit(0);
}