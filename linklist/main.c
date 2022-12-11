#include <stdlib.h>
#include <stdio.h>

#include "linklist.h"

int main(void)
{
  list *list;
  datatype arr[] = {12, 9, 23, 2, 34, 6, 45};
  int i, value = 12, err;
  datatype data;
  list = list_create();
  if (list == NULL)
    exit(1);
  for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
  {
    if (list_order_insert(list, &arr[i]) != 0)
    {
      exit(1);
    }
  }
  list_display(list);

  err = list_delete_at(list, 1, &value);
  if (err)
  {
    exit(1);
  }
  printf("delete:%d\n", value);
  // list_delete(list, &value);
  list_display(list);
  list_destroy(list);
  exit(0);
}