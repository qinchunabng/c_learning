#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int next(int n)
{
  n = n + 1;
  if (n >= THRNUM)
    n = 0;
  return n;
}

static void *thr_func(void *p)
{
  int n = (int)p;
  int c = 'a' + n;
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  while (1)
  {
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    pthread_mutex_lock(&mut);
    while(num != n)
      pthread_cond_wait(&cond, &mut);
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    printf("%c", c);
    num = next(n);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut);
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
  }
  pthread_exit(NULL);
}

int main()
{
  int i, err;
  pthread_t tid[THRNUM];

  for (i = 0; i < THRNUM; i++)
  {
    pthread_mutex_init(&mut, NULL);

    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    err = pthread_create(tid + i, NULL, thr_func, (void *)i);
    if (err)
    {
      fprintf(stderr, "pthread_create():%s\n", strerror(err));
      exit(1);
    }
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  alarm(5);
  for (i = 0; i < THRNUM; i++)
  {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mut);
  pthread_cond_destroy(&cond); 
  exit(0);
}