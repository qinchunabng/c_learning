#include <stdlib.h>
#include <stdio.h>

struct node_st
{
  int coef;
  int exp;
  struct node_st *next;
};

struct node_st *poly_create(int a[][2], int n)
{
  struct node_st *head, *p, *cur;
  int i;
  head = malloc(sizeof(*head));
  if (head == NULL)
  {
    return NULL;
  }
  head->next = NULL;
  cur = head;
  for (i = 0; i < n; i++)
  {
    p = malloc(sizeof(*p));
    if (p == NULL)
    {
      return NULL;
    }
    p->coef = a[i][0];
    p->exp = a[i][1];
    p->next = NULL;
    cur->next = p;
    cur = p;
  }
  return head;
}
void poly_show(struct node_st *me)
{
  struct node_st *cur;
  for (cur = me->next; cur != NULL; cur = cur->next)
  {
    printf("(%d %d)\n", cur->coef, cur->exp);
  }
}

void poly_union(struct node_st *p1, struct node_st *p2)
{
  struct node_st *p, *q, *r;
  p = p1->next;
  q = p2->next;
  r = p1;
  while (p && q)
  {
    if (p->exp < q->exp)
    {
      r->next = p;
      r = p;
      p = p->next;
    }
    else if (p->exp > q->exp)
    {
      r->next = q;
      r = q;
      q = q->next;
    }
    else
    {
      p->coef += q->coef;
      // after add ,result is not zero.
      if (p->coef)
      {
        r->next = p;
        r = p;
        p = p->next;
        q = q->next;
      }
    }
  }
  if (p == NULL)
  {
    r->next = q;
  }
  else
    r->next = p;
}

int main(void)
{
  int a[][2] = {{5, 0}, {2, 3}, {8, 8}, {3, 16}};
  int b[][2] = {{6, 1}, {16, 6}, {-8, 8}};
  struct node_st *p1, *p2;
  p1 = poly_create(a, 4);
  p2 = poly_create(b, 3);
  if (p1 == NULL || p2 == NULL)
  {
    exit(1);
  }
  poly_show(p1);
  printf("\n");
  poly_show(p2);
  printf("\n");
  poly_union(p1, p2);
  poly_show(p1);
  exit(0);
}