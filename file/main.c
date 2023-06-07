#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void test(){
  int count=0;
  FILE *fp=NULL;
  while(1){
    fp=fopen("/tmp","r");
    if(fp==NULL){
      perror("fopen()");
      break;
    }
    count++;
  }
  printf("count=%d\n",count);
}

void test1(){
  char buf[1024];
  int year=2023,month=6,day=5;
  sprintf(buf,"%d-%d-%d", year, month, day);
  printf("%s\n", buf);
}

void test2(){
  printf("Before while()");
  fflush(stdout);

  while(1);

  printf("After while()");
  fflush(NULL);
}

int main()
{
  // FILE *fp;
  // fp = fopen("tmp", "r");
  // if (fp == NULL)
  // {
  //   perror("fopen()");
  //   // fprintf(stderr, "fopen(): %s\n", strerror(errno));
  //   exit(1);
  // }
  // puts("OK");
  // fclose(fp);
  // test();

  // int i=atoi("123a456");
  // printf("%d\n", i);
  // test1();

  test2();
  return 0;
}