#ifndef NOHEAD_H__

#define NOHEAD_H__

#define NAMESIZE 32

struct score_st
{
  int id;
  char name[NAMESIZE];
  int math;
  int chinese;
};

/**
 * no head link list implement
 */
typedef struct node_st
{
  struct score_st data;
  struct node_st *next;
} list;

int list_insert(list **, const struct score_st *data);
void list_show(list *list);
int list_delete(list **list);
struct score_st *list_find(list *list, int id);
void list_destroy(list *list);
#endif