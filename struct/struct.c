#include <stdlib.h>
#include <stdio.h>

struct simple_st{
    int i;
    float f;
    char ch;
}__attribute__((packed));


int main(){
    struct simple_st a;
    struct simple_st *p=&a;
    
    printf("sizeof(point) = %d\n", sizeof(p));
    printf("sizeof(struct) = %d\n", sizeof(a));
    exit(0);
}