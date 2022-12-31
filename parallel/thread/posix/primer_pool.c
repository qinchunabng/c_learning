#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

static void *thr_prime(void *p);

int main()
{
  int i;
  int err;
  pthread_t tid[THRNUM];
  for (i = 0; i < THRNUM; i++)
  {
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    err = pthread_create(tid + i, NULL, thr_prime, (void *)i);
    if (err)
    {
      fprintf(stderr, "pthread_create():%s\n", strerror(err));
      exit(1);
    }
  }
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  for (i = LEFT; i <= RIGHT; i++)
  {
    pthread_mutex_lock(&mut_num);

    while (num != 0)
    {
    //   pthread_mutex_unlock(&mut_num);
    //   sched_yield();
    //   pthread_mutex_lock(&mut_num);
      pthread_cond_wait(&cond_num, &mut_num);
    }
    num = i;
    pthread_cond_signal(&cond_num);
    pthread_mutex_unlock(&mut_num);
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  pthread_mutex_lock(&mut_num);
  while (num != 0)
  {
    // pthread_mutex_unlock(&mut_num);
    // sched_yield();
    // pthread_mutex_lock(&mut_num);
    pthread_cond_wait(&cond_num, &mut_num);
  }
  num = -1;
  pthread_cond_broadcast(&cond_num);
  pthread_mutex_unlock(&mut_num);

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  for (i = 0; i < THRNUM; i++)
  {
    pthread_join(tid[i], NULL);
  }
  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  pthread_mutex_destroy(&mut_num);
  pthread_cond_destroy(&cond_num);
  exit(0);
}

static void *thr_prime(void *p)
{
  int i, j, flag;
  while (1)
  {
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    pthread_mutex_lock(&mut_num);
    while (num == 0)
    {
      // pthread_mutex_unlock(&mut_num);
      // sched_yield();
      // pthread_mutex_lock(&mut_num);
      pthread_cond_wait(&cond_num, &mut_num);
    }
    if (num == -1)
    {
      pthread_mutex_unlock(&mut_num);
      break;
    }
    i = num;
    num = 0;
    pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);

    flag = 1;
    // printf("%s:%d\ti=%d\tflag=%d\n", __FUNCTION__, __LINE__, i, flag);
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
    // printf("%s:%d\tflag=%d\n", __FUNCTION__, __LINE__, flag);
    if (flag)
      printf("[%d]%d is a primer.\n", (int)p, i);
  }
  pthread_exit(NULL);
}