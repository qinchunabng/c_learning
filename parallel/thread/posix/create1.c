#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static void *func(void *ptr)
{
  puts("Thread is working.");
  pthread_exit(NULL);
  // return NULL;
}

int main()
{
  int err;
  pthread_t tid;
  puts("Begin!");

  err = pthread_create(&tid, NULL, func, NULL);
  if (err)
  {
    fprintf(stderr, "pthread_create():%s\n", strerror(err));
    exit(1);
  }
  pthread_join(tid, NULL);
  puts("End!");
  exit(0);
}