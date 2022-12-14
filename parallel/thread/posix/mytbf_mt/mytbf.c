#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#include "mytbf.h"

#define MYTBF_MAX 1024

static struct mytbf_st *job[MYTBF_MAX];
static volatile int inited = 0;
// static struct sigaction alrm_sa_save;

static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_t tid_alrm;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
// typedef void (*sighandler_t)(int);

// static sighandler_t alrm_handler_save;

struct mytbf_st
{
  int cps;
  int burst;
  int token;
  int pos;
  pthread_mutex_t mut;
  pthread_cond_t cond;
};

static void *thr_alrm(void *p)
{
  int i;

  // printf("SI_USER=%d  SI_TIMER=%d SI_TKILL=%d SIGALRM=%d\n", SI_USER, SI_TIMER, SI_TKILL, SIGALRM);
  // printf("%s:%d infp->si_code:%d \n", __FUNCTION__, __LINE__, infp->si_code);
  // if (infp->si_code != SI_KERNEL && infp->si_code != SI_USER)
  //   return;

  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  // alarm(1);
  while (1)
  {
    pthread_mutex_lock(&mut_job);
    for (i = 0; i < MYTBF_MAX; i++)
    {
      // printf("%s:%d job[%d]=\n", __FUNCTION__, __LINE__, i);

      if (job[i] == NULL)
        continue;
      pthread_mutex_lock(&job[i]->mut);
      job[i]->token += job[i]->cps;
      if (job[i]->token > job[i]->burst)
        job[i]->token = job[i]->burst;
      pthread_cond_signal(&job[i]->cond);
      pthread_mutex_unlock(&job[i]->mut);
    }
    pthread_mutex_unlock(&mut_job);
    sleep(1);
  }
}

static void module_unload()
{
  int i;
  // struct itimerval itv;

  // sigaction(SIGALRM, &alrm_sa_save, NULL);

  // itv.it_interval.tv_sec = 1;
  // itv.it_interval.tv_usec = 0;
  // itv.it_value.tv_sec = 1;
  // itv.it_value.tv_usec = 0;
  // setitimer(ITIMER_REAL, &itv, NULL);
  // signal(SIGALRM, alrm_handler_save);
  // alarm(0);
  pthread_cancel(tid_alrm);
  pthread_join(tid_alrm, NULL);

  for (i = 0; i < MYTBF_MAX; i++)
  {
    if (job[i] != NULL)
    {
      mytbf_destory(job[i]);
    }
  }

  pthread_mutex_destroy(&mut_job);
}

static void module_load()
{
  // alrm_handler_save = signal(SIGALRM, alrm_handler);
  // alarm(1);
  // printf("%s:%d\n", __FUNCTION__, __LINE__);
  // struct sigaction sa;
  // struct itimerval itv;

  // sa.sa_sigaction = alrm_action;
  // sigemptyset(&sa.sa_mask);
  // sa.sa_flags = SA_SIGINFO;

  // if (sigaction(SIGALRM, &sa, &alrm_sa_save) < 0)
  // {
  //   perror("sigaction()");
  //   exit(0);
  // }
  // // printf("%s:%d\n", __FUNCTION__, __LINE__);

  // itv.it_interval.tv_sec = 1;
  // itv.it_interval.tv_usec = 0;
  // itv.it_value.tv_sec = 1;
  // itv.it_value.tv_usec = 0;
  // if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
  // {
  //   perror("setitimer()");
  //   exit(1);
  // }
  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  int err;

  err = pthread_create(&tid_alrm, NULL, thr_alrm, NULL);
  if (err)
  {
    fprintf(stderr, "pthread_create():%s\n", strerror(err));
    exit(1);
  }
  atexit(module_unload);
}

static int get_free_pos_unlocked(void)
{
  int i;
  for (i = 0; i < MYTBF_MAX; i++)
  {
    if (job[i] == NULL)
      return i;
  }
  return -1;
}

static int min(int a, int b)
{
  return a < b ? a : b;
}

mytbf_t *mytbf_init(int cps, int burst)
{
  struct mytbf_st *me;
  int pos;

  // if (!inited)
  // {
  //   // printf("%s:%d\n", __FUNCTION__, __LINE__);

  //   module_load();
  //   inited = 1;
  // }

  pthread_once(&init_once, module_load);

  me = malloc(sizeof(*me));
  if (me == NULL)
    return NULL;

  me->token = 0;
  me->burst = burst;
  me->cps = cps;
  pthread_mutex_init(&me->mut, NULL);
  pthread_cond_init(&me->cond, NULL);

  pthread_mutex_lock(&mut_job);
  pos = get_free_pos_unlocked();
  if (pos < 0)
  {
    pthread_mutex_unlock(&mut_job);
    free(me);
    return NULL;
  }
  me->pos = pos;
  job[pos] = me;
  pthread_mutex_unlock(&mut_job);

  return me;
}

int mytbf_fetch(mytbf_t *ptr, int count)
{
  struct mytbf_st *me = ptr;
  int n;
  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  if (count <= 0)
    return -EINVAL;
  // printf("%s:%d me=%p, token=%d\n", __FUNCTION__, __LINE__, me, me->token);

  pthread_mutex_lock(&me->mut);
  while (me->token <= 0)
  {
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    // pause();
    // pthread_mutex_unlock(&me->mut);
    // sched_yield();
    // pthread_mutex_unlock(&me->mut);
    pthread_cond_wait(&me->cond, &me->mut);
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  n = min(me->token, count);
  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  me->token -= n;
  pthread_mutex_unlock(&me->mut);
  return n;
}

int mytbf_returntoken(mytbf_t *ptr, int count)
{
  struct mytbf_st *me = ptr;
  if (count <= 0)
    return -EINVAL;

  pthread_mutex_lock(&me->mut);
  me->token += count;
  if (me->token > me->burst)
    me->token = me->burst;
  pthread_cond_broadcast(&me->cond);
  pthread_mutex_unlock(&me->mut);
  return count;
}

int mytbf_destory(mytbf_t *ptr)
{
  struct mytbf_st *me = ptr;
  pthread_mutex_lock(&mut_job);
  job[me->pos] = NULL;
  pthread_mutex_unlock(&mut_job);
  pthread_cond_destroy(&me->cond);
  pthread_mutex_destroy(&me->mut);
  free(me);
  return 0;
}