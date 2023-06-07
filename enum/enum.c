#include <stdio.h>
#include <stdlib.h>

enum day{
    MON = 1,
    TUE,
    WED,
    THR,
    FRI,
    SAT,
    SUN
};

int main(){

    enum day a = FRI;

    printf("%d\n", a);
    exit(0);
}