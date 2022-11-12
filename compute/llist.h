#ifndef LLIST_H__

#define LLIST_H__

#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

typedef void LLIST;

typedef void llist_op(const void *);

typedef int llist_cmp(const void *, const void *);

LLIST *llist_create(int size);
void llist_destroy(LLIST *);
int llist_insert(LLIST *, const void *data, int mode);
int llist_isempty(LLIST *);

int llist_find(LLIST *ptr, const void *key, llist_cmp *cmp, void *data);
int llist_fetch(LLIST *, const void *key, llist_cmp *, void *data);
int llist_delete(LLIST *, const void *key, llist_cmp *);

void llist_travel(LLIST *, llist_op *);

#endif