#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

struct llist_node_st
{
  struct llist_node_st *prev;
  struct llist_node_st *next;
  char data[0];
};

struct head_st
{
  int size;
  struct llist_node_st head;
  int (*insert)(LLIST *, const void *, int);
  int (*find)(LLIST *, const void *, llist_cmp *, void *);
  int (*fetch)(LLIST *, const void *, llist_cmp *, void *);
  int (*delete)(LLIST *, const void *, llist_cmp *);
  void (*travel)(LLIST *, llist_op *);
};

LLIST *llist_create(int size)
{
  struct head_st *handler;
  // printf("%s:%d,size:%d\n", __FUNCTION__, __LINE__, size);
  handler = malloc(sizeof(*handler));
  if (handler == NULL)
  {
    fprintf(stderr, "malloc handler failed.\n");
    return NULL;
  }

  handler->size = size;
  handler->head.prev = &handler->head;
  handler->head.next = &handler->head;

  handler->insert = llist_insert;
  handler->find = llist_find;
  handler->fetch = llist_fetch;
  handler->delete = llist_delete;
  handler->travel = llist_travel;
  return handler;
}

int llist_isempty(LLIST *ptr)
{
  struct head_st *handler = ptr;
  return ptr == NULL || handler->head.next == &handler->head;
}

void llist_destroy(LLIST *ptr)
{
  struct head_st *handler = ptr;
  struct llist_node_st *cur, *next;
  for (cur = handler->head.next; cur != &handler->head; cur = next)
  {
    next = cur->next;
    free(cur);
  }
  free(handler);
}
int llist_insert(LLIST *ptr, const void *data, int mode)
{
  struct head_st *handler = ptr;
  struct llist_node_st *newnode;
  newnode = malloc(sizeof(*newnode) + handler->size);
  if (newnode == NULL)
  {
    return -1;
  }

  memcpy(newnode->data, data, handler->size);
  if (mode == LLIST_FORWARD)
  {
    newnode->prev = &handler->head;
    newnode->next = handler->head.next;
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
  }
  else if (mode == LLIST_BACKWARD)
  {
    newnode->prev = handler->head.prev;
    newnode->next = &handler->head;
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
  }
  else
  {
    return -3;
  }
  return 0;
}

// this function don't need extern
static struct llist_node_st *find_(LLIST *ptr, const void *key, llist_cmp *cmp)
{
  struct head_st *handler = ptr;
  struct llist_node_st *cur;
  for (cur = handler->head.next; cur != &handler->head; cur = cur->next)
  {
    if (cmp(key, cur->data) == 0)
    {
      return cur;
    }
  }
  return NULL;
}

int llist_find(LLIST *ptr, const void *key, llist_cmp *cmp, void *data)
{
  struct head_st *handler = ptr;
  struct llist_node_st *node;
  node = find_(ptr, key, cmp);
  if (node == NULL)
    return -1;
  memcpy(data, node->data, handler->size);
  return 0;
}

int llist_fetch(LLIST *ptr, const void *key, llist_cmp *cmp, void *data)
{
  struct head_st *handler = ptr;
  struct llist_node_st *node;
  node = find_(handler, key, cmp);
  if (node == NULL)
  {
    return -1;
  }
  if (data != NULL)
  {
    memcpy(data, node->data, handler->size);
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
  return 0;
}

int llist_delete(LLIST *ptr, const void *key, llist_cmp *cmp)
{
  struct llist_node_st *node;
  node = find_(ptr, key, cmp);
  if (node == NULL)
  {
    return -1;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
  return 0;
}

void llist_travel(LLIST *ptr, llist_op *op)
{
  struct head_st *handler = ptr;
  struct llist_node_st *cur, *next;
  for (cur = handler->head.next; cur != &handler->head; cur = next)
  {
    next = cur->next;
    op(cur->data);
  }
}
