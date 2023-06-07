#include <stdio.h>
#include <stdlib.h>

void test(){
    int *p;
    int **q;
    float *f;
    double *d;
    char *c;

    printf("%d\n", sizeof(p));
    printf("%d\n", sizeof(q));
    printf("%d\n", sizeof(f));
    printf("%d\n", sizeof(d));
    printf("%d\n", sizeof(c));
}

void test1(){
    int *p;
    printf("%d\n", *p);
}

void test3(){
    int a[] = {1,2,3};
    int i;
    int *p = a;
    for(i = 0;i<sizeof(a)/sizeof(a[0]);i++){
        printf("%p = %d\n", &a[i], a[i]);
        printf("%p = %d\n", p+i, *(p+i));
    }
}

void test4(){
    int i,j;
    int a[2][3] = {1,2,3,4,5,6};
    int *p=*a;
    int (*q)[3] = a; 

    printf("p=%d\n", *p);
    printf("%p %p\n", a, a+1);
    printf("%p %p\n", q, q+1);

    for(i =0; i< 2;i++){
        for(j=0;j<3;j++){
            printf("%p -> %d\n",*(a+i) + j, *(*(a+i) + j));
            printf("%p -> %d\n",*(q+i) + j, *(*(q+i) + j));
        }   
        printf("\n");
    }
}

void test5(){
    const float pi = 3.14;
    float *p = &pi;
    *p = 3.14159;
    printf("%f\n", pi);
}

void test6(){
    int i;
    char *name[5]={"Follow me","Basic","Great","Fortran","Computer"};
    for(i=0;i<5;i++){
        puts(name[i]);
    }
}

void test7(int *p,int size){
    int i;
    for(i=0;i<size;i++){
        printf("%4d", p[i]);
    }
    printf("\n");
}

void test8(int (*p)[4],int m,int n){
    int i,j;   
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            // printf("%4d", p[i][j]);
            printf("%4d", *(*(p+i)+j));
        }
        printf("\n");
    }
}

int add(int a, int b){
    return a + b;
}

int sub(int a,int b){
    return a - b;
}

int main(){
    // int i = 1;
    // int *p;
    // int **q;

    // i = 1;
    // p = &i;
    // q = &p;
    // printf("i=%d\n", i);
    // printf("&i=%p\n",&i);
    // printf("p=%p\n", p);
    // printf("&p=%p\n", &p);
    // printf("*p=%d\n", *p);
    // printf("q=%p\n", q);
    // printf("*q=%p\n", *q);
    // printf("**q=%d\n", **q);

    // test();

    // test1();

    // test3();

    // test4();
    
    // test5();

    // test6();

    // int a[] = {1,2,3,4,5,6};
    // printf("%s:%d\n", __FUNCTION__, sizeof(a));
    // test7(a,sizeof(a)/sizeof(*a));

    // int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    // test7(&a[0][0], sizeof(a)/sizeof(a[0][0]));
    // test8(a,sizeof(a)/sizeof(a[0]),sizeof(a[0])/sizeof(a[0][0]));

    // int a = 10, b = 20;
    // int res;
    // int (*p)(int,int);

    // p = add;
    // res = p(a,b);
    // printf("ret=%d\n", res);

    int i;
    int a=20,b=10;
    int (*p[2])(int,int);
    int res;

    p[0]=add;
    p[1]=sub;
    for(i=0;i<2;i++){
        res=p[i](a,b);
        printf("%d\n",res);
    }

    exit(0);
}