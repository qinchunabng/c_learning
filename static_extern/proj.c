#include <stdio.h>
#include <stdlib.h>

#include "proj.h"

static int i = 10;

extern int j;

void test_static(void)
{
  printf("[%s]:i=%d\n", __FUNCTION__, i);
}

void test_extern(void)
{
  printf("[%s]:j=%d\n", __FUNCTION__, j);
}