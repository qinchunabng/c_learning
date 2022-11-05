#include <stdlib.h>
#include <stdio.h>

#include "nohead.h"

int main(void)
{
  int i, ret;
  int id = 3;
  list *list = NULL;
  struct score_st tmp, *ptr;
  for (i = 0; i < 7; i++)
  {
    tmp.id = i;
    snprintf(tmp.name, NAMESIZE, "stu%d", i);
    tmp.math = rand() % 100;
    tmp.chinese = rand() % 100;
    ret = list_insert(&list, &tmp);
    if (ret != 0)
    {
      fprintf(stderr, "Insert failed.\n");
      exit(0);
    }
  }

  list_show(list);

  list_delete(&list);
  printf("\n\n");
  list_show(list);

  ptr = list_find(list, id);
  if (ptr == NULL)
  {
    printf("Cannot find data which id is %d.\n", id);
  }
  else
  {
    printf("%d %s %d %d\n", ptr->id, ptr->name, ptr->math, ptr->chinese);
  }

  list_destroy(list);
  exit(0);
}
