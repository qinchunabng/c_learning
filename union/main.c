#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union test_un
{
  int i;
  float f;
  double d;
  char ch;
};

union
{
  struct
  {
    uint16_t i;
    uint16_t j;
  } x;
  uint32_t y;
} a;

union
{
  struct
  {
    char a : 1;
    char b : 2;
    char c : 1;
  } x;
  int y;
} w;

int main(void)
{
  // union test_un a;
  // a.f = 345.678;
  // printf("%d\n", sizeof(a));
  // printf("%f\n", a.f);
  // this is meaningless.
  // printf("%d\n", a.i);

  // unsigned int i = 0x11223344;
  // printf("%x\n", (i >> 16) + i & 0xFFFF);

  // a.y = 0x11223344;
  // printf("%x\n", a.x.i + a.x.j);

  w.y = 1;
  printf("a=%d,b=%d,c=%d\n", w.x.a, w.x.b, w.x.c);
  exit(0);
}