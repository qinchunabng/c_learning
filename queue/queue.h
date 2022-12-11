#ifndef QUEUE_H__

#define QUEUE_H__

#include "llist.h"

typedef LLIST QUEUE;

QUEUE *queue_create(int size);

int queue_en(QUEUE *, void *);

int queue_de(QUEUE *, void *);

void queue_destroy(QUEUE *);

#endif