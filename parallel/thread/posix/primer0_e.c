#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT - LEFT + 1)

struct thr_arg_st
{
  int n;
};

static void *thr_prime(void *p);

int main()
{
  int i;
  int err;
  pthread_t tid[THRNUM];

  struct thr_arg_st *p;
  void *ptr;

  for (i = LEFT; i <= RIGHT; i++)
  {
    p = malloc(sizeof(*p));
    if (p == NULL)
    {
      perror("malloc()");
      exit(1);
    }
    p->n = i;
    // printf("%s:%d\ti=%d\n", __FUNCTION__, __LINE__, i);
    err = pthread_create(tid + i - LEFT, NULL, thr_prime, p);
    if (err)
    {
      fprintf(stderr, "pthread_create():%s\n", strerror(err));
      exit(1);
    }
  }

  for (i = 0; i < THRNUM; i++)
  {
    pthread_join(tid[i], &ptr);
    // printf("%s:%d\tptr=%p\ti=%d\n", __FUNCTION__, __LINE__, ptr, i);
    free(ptr);
  }

  exit(0);
}

static void *thr_prime(void *p)
{
  int i, j, flag = 1;
  i = ((struct thr_arg_st *)p)->n;
  // printf("%s:%d\tp=%p\n", __FUNCTION__, __LINE__, p);
  for (j = 2; j < i / 2; j++)
  {
    if (i % j == 0)
    {
      // printf("%s:%d\ti=%d\tj=%d\n", __FUNCTION__, __LINE__, i, j);
      // printf("%d %d\n", i, j);
      flag = 0;
      break;
    }
  }
  if (flag)
    printf("%d is a primer.\n", i);

  pthread_exit(p);
}