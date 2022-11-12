#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

STACK *stack_create(int initsize)
{
  return llist_create(initsize);
}

int stack_push(STACK *ptr, void *data)
{
  return llist_insert(ptr, data, LLIST_FORWARD);
}

static int always_match(const void *p1, const void *p2)
{
  return 0;
}

int stack_pop(STACK *ptr, void *data)
{
  return llist_fetch(ptr, (void *)0, always_match, data);
}

int stack_top(STACK *ptr, void *data)
{
  return llist_find(ptr, (void *)0, always_match, data);
}

int stack_isempty(STACK *ptr)
{
  return llist_isempty(ptr);
}

void stack_destroy(STACK *ptr)
{
  llist_destroy(ptr);
}

void stack_travel(STACK *ptr, llist_op *op)
{
  llist_travel(ptr, op);
}