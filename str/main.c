#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 32

void test_strlen()
{
  char str[] = "hello";
  printf("%d\n", strlen(str));
}

void test_str_function()
{
  char str[N] = "hello";
  char str1[N] = "helloa";
  // strcpy(str, "hello");
  // printf("%s\n", str);

  // strncpy(str, "world!", N);
  // printf("%s\n", str);

  // strcat(str, " ");
  // strncat(str, "hello", N);
  // printf("%s\n", str);

  printf("%d\n", strcmp(str, str1));
  printf("%d\n", strncmp(str, str1, 5));
}

void count_word(void)
{

  char str[128];
  int count = 0;
  int j, flag = 0;

  gets(str);

  for (j = 0; j < strlen(str); j++)
  {
    if (str[j] == ' ' || str[j] == '\t')
    {
      flag = 0;
    }
    else
    {
      if (!flag)
      {
        count++;
        flag = 1;
      }
    }
  }
  printf("word count:%d", count);
}

void strinput(void)
{
  char str[N], str1[N], str2[N];
  // array name here itself represents an address.
  scanf("%s%s%s", str, str1, str2);
  printf("%s\n", str);
  printf("%s\n", str1);
  printf("%s\n", str2);
}

int main(void)
{
  // strinput();
  // test_strlen();
  // test_str_function();
  count_word();
  exit(0);
}