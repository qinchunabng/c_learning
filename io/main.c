#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 32

/**
 * int scanf(const char *format, address table)
 */
void test_scanf()
{
  int i;
  float f;
  char ch, str[STRSIZE];
  int ret;

  printf("Please enter:\n");
  // your input string need keep consistency with format,
  // or you won't get your input.
  // scanf("%d,%f", &i, &f);
  // printf("i = %d\n", i);
  // printf("f = %f\n", f);
  // scanf("%s", str);
  // you needn't use '&' operator here, because the array variable itself is a pointer.
  // if your input with some splitter string such as ' ', you only get input content before the splitter string.
  // printf("%s\n", str);

  scanf("%d", &i);
  //'*' is a restaint symbol. it is used to discard some useless strings like '\n'.
  // scanf("%*c%c", &ch);
  // or you can getchar() to skip these string.
  getchar();
  scanf("%c", &ch);
  printf("i = %d,ch = %d\n", i, ch);
}

int main(void)
{
  int i = 123;
  float f = 123.456;
  char str[STRSIZE] = "helloworld";
  double dou = 123.456;

  printf("i = %04d\n", i);
  printf("i = %#x\n", i);
  printf("f = %8.1f\n", f);

  printf("str = %.5s\n", str);
  printf("dou = %lf\n", dou);

  // add '\n' indicate to flush buffer.
  // if you don't add '\n', blow log may not be printed.
  // printf("[%s:%d] before while.\n", __FUNCTION__, __LINE__);
  // while (1)
  //   ;
  // printf("[%s:%d] after while.\n", __FUNCTION__, __LINE__);

  test_scanf();

  exit(0);
}
