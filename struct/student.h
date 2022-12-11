#ifndef STUDENT_H__
#define STUDENT_H__

#define NAMESIZE 1024

typedef struct student_st
{
  int id;
  char *name;
  int year, month, day;
  int math;
  int chinese;
} STU;

void stu_set(STU *p, const STU *q);
void stu_show(STU *p);
void stu_changename(STU *p, char *newname);
void menu();
#endif