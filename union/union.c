#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

union test_un{
    int i;
    float f;
    double d;
    char ch;
};

union {
    struct{
        uint16_t i;
        uint16_t j;
    }x;
    uint32_t y;
} a;

int main(){
    // union test_un a;
    // a.f=345.678;

    // printf("%d\n", sizeof(a));
    // printf("%f\n", a.f);
    // printf("%d\n", a.i);

    a.y=0x11223344;

    printf("%x\n", a.x.i + a.x.j);

    exit(0);
}