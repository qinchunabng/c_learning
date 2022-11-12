#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

typedef int datatype;

static void print_d(const void *ptr)
{
  const datatype *data = ptr;
  printf("%d\n", *data);
}

static void print_c(const void *ptr)
{
  const datatype *data = ptr;
  printf("%c\n", *data);
}

static void compute(STACK *snum, datatype *op)
{
  datatype n1, n2, n;
  stack_pop(snum, &n2);
  stack_pop(snum, &n1);
  switch (*op)
  {
  case '+':
    n = n1 + n2;
    break;
  case '-':
    n = n1 - n2;
    break;
  case '*':
    n = n1 * n2;
    break;
  case '/':
    n = n1 / n2;
    break;
  default:
    exit(1);
  }
  stack_push(snum, &n);
}

static void deal_bracket(STACK *snum, STACK *sop)
{
  datatype old_op;
  stack_top(sop, &old_op);
  while (old_op != '(')
  {
    stack_pop(sop, &old_op);
    compute(snum, &old_op);
    stack_top(sop, &old_op);
  }
  stack_pop(sop, &old_op);
}

static int get_pri(datatype op)
{
  switch (op)
  {
  case '(':
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;

  default:
    exit(1);
  }
}

static void deal_op(STACK *snum, STACK *sop, datatype op)
{
  datatype old_op;
  // printf("\n\n");
  // printf("%s:%c\n", __FUNCTION__, op);
  // printf("snum:\n");
  // stack_travel(snum, print_d);
  // printf("sop:\n");
  // stack_travel(sop, print_c);
  if (stack_isempty(sop) || op == '(')
  {
    stack_push(sop, &op);
    return;
  }
  stack_top(sop, &old_op);
  if (get_pri(op) > get_pri(old_op))
  {
    stack_push(sop, &op);
    return;
  }
  while (get_pri(op) <= get_pri(old_op))
  {
    stack_pop(sop, &old_op);
    compute(snum, &old_op);
    if (stack_isempty(sop))
      break;
    stack_pop(sop, &old_op);
  }
  stack_push(sop, &op);
}

int main(void)
{
  int i, value = 0, flag = 0;
  char str[] = "(11+3)*2-5";
  STACK *snum, *sop;
  datatype old_op, res;
  snum = stack_create(sizeof(datatype));
  if (snum == NULL)
    exit(1);
  sop = stack_create(sizeof(datatype));
  if (sop == NULL)
    exit(1);
  while (str[i] != '\0')
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      value = value * 10 + (str[i] - '0');
      flag = 1;
    }
    else
    {
      if (flag)
      {
        stack_push(snum, &value);
        flag = 0;
        value = 0;
      }
      if (str[i] == ')')
      {
        deal_bracket(snum, sop);
      }
      else // ( + - * /
      {
        deal_op(snum, sop, str[i]);
      }
    }
    i++;
  }
  if (flag)
    stack_push(snum, &value);

  // printf("\n\n");
  // printf("%s:\n", __FUNCTION__);
  // printf("snum:\n");
  // stack_travel(snum, print_d);
  // printf("sop:\n");
  // stack_travel(sop, print_c);
  while (!stack_isempty(sop))
  {
    stack_pop(sop, &old_op);
    compute(snum, &old_op);
  }

  stack_pop(snum, &res);
  printf("result=%d\n", res);
  stack_destroy(snum);
  stack_destroy(sop);
  exit(0);
}