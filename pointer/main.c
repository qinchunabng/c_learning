#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pointer_array(void)
{
  char *name[5] = {"Follow me",
                   "Basic",
                   "Great",
                   "Fortran",
                   "Computer"};
  int i, j, k;
  char *tmp;
  // selective sort
  for (i = 0; i < 5; i++)
  {
    k = i;
    for (j = i + 1; j < 5; j++)
    {
      if (strcmp(name[i], name[j]) > 0)
      {
        k = j;
      }
    }
    if (k != i)
    {
      tmp = name[i];
      name[i] = name[k];
      name[k] = tmp;
    }
  }
  for (i = 0; i < 5; i++)
  {
    puts(name[i]);
  }
}

/**
 * const int *p: 常量指针，指针的指向可以发送变化，指针的值不能发生变化
 * int *const p:
 */
void const_pointer(void)
{
  const float f = 3.14;
  float j = 1.414;
  //常量指针无法改变指针的值，但可以改变指针的指向
  const float *p = &f;
  //指针常量无法改变指向的指向，但可以改变指针的值
  float *const q = &j;
  printf("%f\n", *p);
  p = &j;
  printf("%f\n", *p);
  printf("%f\n", *q);
  // q = &j;
  *q = 1.99;
  printf("%f\n", j);
}

void str_arr(void)
{
  char *str = "hello";
  printf("%d %d\n", sizeof(str), strlen(str));

  // str is a string const,so strcpy cannot be used.
  //  strcpy(str, "world");
  // to change str content,used like below.
  str = "world";
  puts(str);

  // char str[] = "I love china!";
  // char *p = str + 7;
  // puts(str);
  // puts(p);

  // char str[] = "hello";
  // char *p = str;
  // printf("str sizeof: %d, strlen: %d, p sizeof: %d\n", sizeof(str), strlen(str), sizeof(p));
  // printf("*p=%c\n", *p);
  // printf("str:%p\n p:%p\n", str, p);
  // // str is a const.if you want to change it, you must use strcpy function.
  // strcpy(str, "world");
  // puts(str);
}

int main(void)
{
  int i = 0;
  int *p = &i;
  int **q = &p;
  printf("&i=%p\n", &i);
  printf("p=%p\n", p);
  printf("&p=%p\n", &p);
  printf("*q=%p\n", *q);
  // pointer_array();
  // const_pointer();
  // str_arr();
#if 0
  int *p = NULL;
  //
  void *q = NULL;
  int i;
  p = (int[3]){1, 2, 3};
  for (i = 0; i < 3; i++)
  {
    printf("%p->%d\n", p + i, p[i]);
  }
#endif

  // array variable is a constant. you can't change its value.
  // but p is pointer variable, you can change its point.
  // array name is a abstraction about some memory.
  // int a[] = {1, 2, 3};
  // p = a;
  // int i;
  // for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
  // {
  //   // printf("%p=%d\n", a + i, a[i]);
  //   // a[i]: a[i]=*(a+i)=*(p+i)=p[i]
  //   //&a[i]: &a[i]=a+i=p+i=&p[i]
  //   printf("%p=%d\n", p + i, *(p + i));
  // }

  // int i = 0;
  // // pointer
  // int *p = &i;
  // int **q = &p;

#if 0
  char *cp;
  float *fp;
  double *dp;
  // pointer space usage only be related to whether os is 32 bits or 64 bits
  printf("sizeof(i)=%d\n", sizeof(i));
  printf("sizeof(p)=%d\n", sizeof(p));
  printf("sizeof(cp)=%d\n", sizeof(cp));
  printf("sizeof(fp)=%d\n", sizeof(cp));
  printf("sizeof(dp)=%d\n", sizeof(dp));
#endif

  // print above variables
  // printf("i=%d\n", i);
  // printf("&i=%p\n", &i);
  // printf("p=%p\n", p);
  // printf("&p=%p\n", &p);
  // printf("*p=%d\n", *p);
  // printf("q=%p\n", q);
  // printf("*q=%p\n", *q);
  // printf("**q=%d\n", **q);
  // exit(0);
}