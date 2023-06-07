#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 3

int main(){
    // int i;
    // int ret;
    // float f;
    char str[STRSIZE];
    // char ch;

    printf("Please enter:\n");

    // scanf("%d,%f",&i,&f);
    // printf("i = %d\n", i);
    // printf("f = %f\n", f);
    // scanf("%s", str);
    // printf("%s\n", str);

    // while(1){
    //     ret = scanf("%d",&i);
    //     if(ret != 1){
    //         printf("Enter error!\n");
    //         break;
    //     }
    //     printf("i = %d\n", i);
    // }

    // scanf("%d", &i);
    // scanf("%*c%c", &ch);
    // printf("i = %d, ch = %c\n", i, ch);

    gets(str);
    printf("%s\n", str);
    puts(str);
    exit(0);
}