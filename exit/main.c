#include <stdlib.h>
#include <stdio.h>

static void f1(){
    puts("f1 is running.");
}

static void f2(){
    puts("f2 is running.");
}

static void f3(){
    puts("f3 is running.");
}

int main(){
    puts("Begin!");

    atexit(f1);
    atexit(f2);
    atexit(f3);
    
    puts("End!");
    exit(0);
}