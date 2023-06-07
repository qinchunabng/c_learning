#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test1(){
    char str[]="I love china!";
    char *p = str + 7;

    puts(str);
    puts(p);
}

void test2(){
    char str[]="hello";
    // str="world";
    strcpy(str, "world");
    puts(str);
}

void test3(){
    char *p = "hello";
    p="world";
    puts(p);
}

int main(){
    // char str[] = "hello\0abc";

    // str="abc";

    // printf("%d\n", strlen(str));
    // printf("%d\n", sizeof(str));

    // test1();
    test2();

    test3();

    return 0;
}