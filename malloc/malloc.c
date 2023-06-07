#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char *s=NULL;
    s=malloc(sizeof(char) * 6); 
    if(s == NULL){
        printf("malloc() error!\n");
        exit(1);
    }   
    strcpy(s, "hello");

    printf("%ld\n", strlen(s));
    printf("%s\n", (char *)s);
    free(s);

    exit(0);
}