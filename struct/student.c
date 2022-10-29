#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void stu_set(struct student_st *p, const struct student_st *q)
{
  // p->id = 100;
  // // As name is a constant, it should be assigned by strcpy.
  // strncpy(p->name, "Alan", NAMESIZE);
  // p->math = 90;
  // p->chinese = 98;
  *p = *q;
}

void stu_show(struct student_st *p)
{
  printf("%d %s %d %d\n", p->id, p->name, p->math, p->chinese);
}

void stu_changename(struct student_st *p, char *newname)
{
  strncpy(p->name, newname, NAMESIZE);
}

void menu()
{
  printf("\n1 set\n2 change name\n3 show\n");
  printf("Please enter the num:");
}