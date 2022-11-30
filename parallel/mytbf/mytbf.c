#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "mytbf.h"

#define MYTBF_MAX 1024

static struct mytbf_st *job[MYTBF_MAX];
static volatile int inited = 0;

typedef void (*sighandler_t)(int);

static sighandler_t alrm_handler_save;

struct mytbf_st
{
  int cps;
  int burst;
  int token;
  int pos;
};

static void alrm_handler(int s)
{
  int i;
  alarm(1);
  for (i = 0; i < MYTBF_MAX; i++)
  {
    // printf("%s:%d job[%d]=\n", __FUNCTION__, __LINE__);
    if (job[i] == NULL)
      continue;
    job[i]->token += job[i]->cps;
    if (job[i]->token > job[i]->burst)
      job[i]->token = job[i]->burst;
  }
}

static void module_unload()
{
  int i;
  signal(SIGALRM, alrm_handler_save);
  alarm(0);
  for (i = 0; i < MYTBF_MAX; i++)
    free(job[i]);
}

static void module_load()
{
  alrm_handler_save = signal(SIGALRM, alrm_handler);
  alarm(1);
  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  atexit(module_unload);
}

static int get_free_pos(void)
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

  if (!inited)
  {
    // printf("%s:%d\n", __FUNCTION__, __LINE__);

    module_load();
    inited = 1;
  }
  pos = get_free_pos();
  if (pos < 0)
    return NULL;

  me = malloc(sizeof(*me));
  if (me == NULL)
    return NULL;

  me->token = 0;
  me->burst = burst;
  me->cps = cps;
  me->pos = pos;

  job[pos] = me;
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

  while (me->token <= 0)
  {
    // printf("%s:%d\n", __FUNCTION__, __LINE__);
    pause();
  }

  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  n = min(me->token, count);
  // printf("%s:%d\n", __FUNCTION__, __LINE__);

  me->token -= n;
  return n;
}

int mytbf_returntoken(mytbf_t *ptr, int count)
{
  struct mytbf_st *me = ptr;
  if (count <= 0)
    return -EINVAL;

  me->token += count;
  if (me->token > me->burst)
    me->token = me->burst;
  return count;
}

int mytbf_destory(mytbf_t *ptr)
{
  struct mytbf_st *me = ptr;

  job[me->pos] = NULL;
  free(me);
  return 0;
}