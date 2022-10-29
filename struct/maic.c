#include <stdlib.h>
#include <stdio.h>

#include "student.h"

struct simple_st
{
  int i;
  char ch;
  float f;
  // char ch1;
} __attribute__((packed));

int main(void)
{
  // initialize a struct
  /*
    a.i = 112233;
    printf("%d %f %c\n", a.i, a.f, a.ch);
    */

#if 0
  // partial initialization
  struct student_st stu = {.math = 98, .chinese = 97};
  // define a struct pointer
  struct student_st *p = &stu;
  printf("%d\t%d\n", p->math, p->chinese);
#endif

  // struct simple_st a;
  // struct simple_st *p = &a;
  // printf("sizeof(struct)=%d\n", sizeof(a));
  // printf("sizeof(pointer)=%d\n", sizeof(p));

  struct student_st stu, tmp;
  char newname[NAMESIZE];
  int choice;

  do
  {
    menu();
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("Please enter for the stu[id name math chinese]:\n");
      scanf("%d%s%d%d", &tmp.id, tmp.name, &tmp.math, &tmp.chinese);
      stu_set(&stu, &tmp);
      break;
    case 2:
      printf("please enter the newname:\n");
      scanf("%s", newname);
      stu_changename(&stu, newname);
      break;
    case 3:
      stu_show(&stu);
      break;
    default:
      exit(1);
      break;
    }
  } while (1);

  exit(0);
}