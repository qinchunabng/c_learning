#ifndef STACK_H__

#define STACK_H__

#include "llist.h"

typedef LLIST STACK;

STACK *stack_create(int initsize);

int stack_push(STACK *, void *);

int stack_pop(STACK *, void *);

int stack_top(STACK *, void *);

int stack_isempty(STACK *);

void stack_destroy(STACK *);

#endif