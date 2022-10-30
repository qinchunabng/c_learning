#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void stu_set(STU *p, const STU *q)
{
  // p->id = 100;
  // // As name is a constant, it should be assigned by strcpy.
  // strncpy(p->name, "Alan", NAMESIZE);
  // p->math = 90;
  // p->chinese = 98;
  p->id = q->id;
  p->name = malloc(strlen(q->name) + 1);
  if (p->name == NULL)
    exit(1);
  strcpy(p->name, q->name);
  p->math = q->math;
  p->chinese = q->chinese;
}

void stu_show(STU *p)
{
  printf("%d %s %d %d\n", p->id, p->name, p->math, p->chinese);
}

void stu_changename(STU *p, char *newname)
{
  free(p->name);
  p->name = malloc(strlen(newname) + 1);
  strcpy(p->name, newname);
}

void menu()
{
  printf("\n1 set\n2 change name\n3 show\n");
  printf("Please enter the num:");
}