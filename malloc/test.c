#include <stdlib.h>
#include <stdio.h>

void func(int *p,int n){
    p=malloc(n);
    if(p == NULL){
        exit(1);
    }
}


void test(){
    int *p=NULL;
    p=malloc(sizeof(int));
    if(p==NULL){
        printf("malloc() error!\n");
        exit(1);
    }

    *p=10;
    printf("%p=%d\n", p, *p);

    free(p);
    p=NULL;
    printf("%p=%d\n", p, *p);

    *p=20;
    printf("%p=%d\n", p, *p);
}

int main(){
    // int num = 10;
    // int *p = NULL;

    // func(p,num);
    // free(p);

    test();

    exit(0);
}