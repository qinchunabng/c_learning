#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

static jmp_buf buf;

static void d()
{
  printf("%s():Begin.\n", __FUNCTION__);
  printf("%s():This is d().\n", __FUNCTION__);
  longjmp(buf, 6);
  printf("%s():End.\n", __FUNCTION__);
}

static void c()
{
  printf("%s():Begin.\n", __FUNCTION__);
  printf("%s():Call d().\n", __FUNCTION__);
  d();
  printf("%s():d() returned.\n", __FUNCTION__);
  printf("%s():End.\n", __FUNCTION__);
}

static void b()
{
  printf("%s():Begin.\n", __FUNCTION__);
  printf("%s():Call c().\n", __FUNCTION__);
  c();
  printf("%s():c() returned.\n", __FUNCTION__);
  printf("%s():End.\n", __FUNCTION__);
}

static void a()
{
  int ret;
  printf("%s():Begin.\n", __FUNCTION__);
  ret = setjmp(buf);
  if (ret == 0)
  {
    printf("%s():Call b().\n", __FUNCTION__);
    b();
  }
  else
  {
    printf("%s:Jumped back here with code %d.\n", __FUNCTION__, ret);
  }

  printf("%s():b() returned.\n", __FUNCTION__);
  printf("%s():End.\n", __FUNCTION__);
}

int main()
{
  printf("%s():Begin.\n", __FUNCTION__);
  printf("%s():Call a().\n", __FUNCTION__);
  a();
  printf("%s():a() returned.\n", __FUNCTION__);
  printf("%s():End.\n", __FUNCTION__);

  exit(0);
}