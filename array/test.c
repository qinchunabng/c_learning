#include <stdlib.h>
#include <stdio.h>

void test1(){
    int a[2][3]={{1,2,3},{4,5,6}};
    int i,j;

    printf("a = %p\n", a + 0);
    printf("a = %p\n", a + 1);
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            printf("%p --> %d\n", &a[i][j], a[i][j]);
        }
    }
}

int main(){
//     int arr[3] = {1};
//     int i;
//     printf("arr = %p\n", arr);
//     for(i = 0;i < 3; i++)
//         printf("%p --> %d\n", &arr[i], arr[i]);

//     arr[3] = 10;
//     printf("arr[3] = %d\n", arr[3]);

    test1();
    exit(0);
}