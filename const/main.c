#include <stdlib.h>
#include <stdio.h>

#define PI 3.14

#define MAX(a,b) ((a)>(b)?(a):(b))

int max(int a,int b){
    return a > b ? a : b;
}

int main(){
    int a=10,b=20;
    printf("a=%d,b=%d\n",a,b);
    printf("MAX(a,b)=%d\n", MAX(a,b));
    printf("max(a,b)=%d\n", max(a,b));
    printf("a=%d,b=%d\n",a,b);

    exit(0);
}