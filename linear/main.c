#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

int main(void)
{
  sqlist *list;
  sqlist *list1;
  datatype arr[] = {11, 22, 33, 44, 55, 66};
  datatype arr1[] = {10, 20, 30, 40, 50};
  int i, err;
  // list = sqlist_create();
  sqlist_create1(&list);
  sqlist_create1(&list1);
  if (list == NULL || list1 == NULL)
  {
    fprintf(stderr, "sql_create failed!\n");
    exit(1);
  }
  for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
  {
    if ((err = sqlist_insert(list, i, &arr[i])) != 0)
    {
      if (err == -1)
      {
        fprintf(stderr, "The array is full.\n");
      }
      else if (err == -2)
      {
        fprintf(stderr, "the position you  want to insert is wrong.\n");
      }
      else
      {
        fprintf(stderr, "Error!\n");
      }
      exit(1);
    }
  }
  sqlist_display(list);

  for (i = 0; i < sizeof(arr1) / sizeof(*arr1); i++)
  {
    if ((err = sqlist_insert(list1, i, &arr1[i])) != 0)
    {
      if (err == -1)
      {
        fprintf(stderr, "The array is full.\n");
      }
      else if (err == -2)
      {
        fprintf(stderr, "the position you  want to insert is wrong.\n");
      }
      else
      {
        fprintf(stderr, "Error!\n");
      }
      exit(1);
    }
  }
  sqlist_display(list1);

  sqlist_union(list, list1);

  // sqlist_delete(list, 1);
  sqlist_display(list);
  // sqlist_destroy(list);
  exit(0);
}