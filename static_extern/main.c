#include <stdio.h>
#include <stdlib.h>

#include "proj.h"

static int i = 100;

int j = 99;

int main(void)
{
  printf("[%s]:i=%d\n", __FUNCTION__, i);
  test_static();

  printf("[%s]:j=%d\n", __FUNCTION__, j);
  test_extern();
  exit(0);
}