#ifndef STUDENT_H__
#define STUDENT_H__

#define NAMESIZE 32

struct student_st
{
  int id;
  char name[NAMESIZE];
  int year, month, day;
  int math;
  int chinese;
};

void stu_set(struct student_st *p, const struct student_st *q);
void stu_show(struct student_st *p);
void stu_changename(struct student_st *p, char *newname);
void menu();
#endif